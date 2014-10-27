/**
 * @file BC_Buffer.cpp 
 * @author Brett Crawford
 * @brief A shared, bounded buffer class
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: A sharedbounded buffer class to be used with an implementation
 *  of the producer/consumer problem. The buffer class is to be used in 
 *  conjunction with a shared logger as well as with producers and consumers. 
 *  This class is written for use with windows.
*/

using namespace std;

#include "BC_Buffer.hpp"

/**
 * Constructs a shared, bounded buffer object. The buffer can hold elements
 * of type void* meaning the elements should be allocated on the heap before 
 * insertion into the buffer.
 * 
 * @param[in] size The max number of elements in buffer
 * @param[in] logger A pointer to the shared logger
*/
BC_Buffer::BC_Buffer(size_t size, BC_Logger *logger)
{
	firstFilled = nextEmpty = 0;
	this->size = size;
	this->logger = logger;
	buffer = (void**) calloc(this->size, sizeof(void*));
	mutex_insert_lock = CreateMutex(NULL, FALSE, NULL);
	mutex_remove_lock = CreateMutex(NULL, FALSE, NULL);
	sem_available = CreateSemaphore(NULL, this->size, this->size, NULL);
	sem_unavailable = CreateSemaphore(NULL, 0, this->size, NULL);
}

/**
 * Destroys a buffer object
*/
BC_Buffer::~BC_Buffer()
{
	size_t i;
	WaitForSingleObject(mutex_insert_lock, INFINITE);
	WaitForSingleObject(mutex_remove_lock, INFINITE);
	for(i = firstFilled; i < nextEmpty; i++)
		free(buffer[i % size]);
	free(buffer);
	CloseHandle(mutex_insert_lock);
	CloseHandle(mutex_remove_lock);
	CloseHandle(sem_available);
	CloseHandle(sem_unavailable);
}

/**
 * Inserts an element in the buffer. If the buffer is full, this call will
 * block until the insert can be performed or if the shared insert data of 
 * the buffer is currently in use.
 *
 * @param[in] item A void pointer to the element to be inserted
*/
void BC_Buffer::insert(void *item)
{	
	int l;
	int temp = *(int*) item;
	char *event = (char*) calloc(65, sizeof(char));

	WaitForSingleObject(sem_available, INFINITE);
	WaitForSingleObject(mutex_insert_lock, INFINITE);

	/** CRITICAL SECTION ENTRY */
	buffer[nextEmpty % size] = item;
	nextEmpty++;
	l = nextEmpty;
	sprintf_s(event, 65, "Buffer: %d inserted            nextEmpty: %d", 
		      temp, l);
	logger->log_event(event);
	free(event);
	/** CRITICAL SECTION EXIT */

	ReleaseMutex(mutex_insert_lock);
	ReleaseSemaphore(sem_unavailable, 1, NULL);
}

/**
 * Removes an element from the buffer. If the buffer is empty, this call will
 * block until the remove can be performed or if the shared remove data of the 
 * buffer is currently in use.  
 *
 * @return A void pointer to the element removed from the buffer
*/
void *BC_Buffer::remove()
{
	int f;
	void *item;
	char *event = (char*) calloc(65, sizeof(char));

	WaitForSingleObject(sem_unavailable, INFINITE);
	WaitForSingleObject(mutex_remove_lock, INFINITE);

	/** CRITICAL SECTION ENTRY */
	item = buffer[firstFilled % size];
	buffer[firstFilled % size] = NULL;
	firstFilled++;
	f = firstFilled;
	sprintf_s(event, 65, "Buffer: %d removed           firstFilled: %d", 
		      *(int*)item, f);
	logger->log_event(event);
	free(event);
	/** CRITICAL SECTION EXIT */

	ReleaseMutex(mutex_remove_lock);
	ReleaseSemaphore(sem_available, 1, NULL);

	return item;
}