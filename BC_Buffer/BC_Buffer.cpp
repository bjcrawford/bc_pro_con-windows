/* File: BC_Buffer.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

using namespace std;

#include "BC_Buffer.hpp"


BC_Buffer::BC_Buffer(size_t size, BC_Logger *logger)
{
	first = last = 0;
	this->size = size;
	this->logger = logger;
	buffer = (void**) calloc(this->size, sizeof(void*));
	mutex_lock = CreateMutex(NULL, FALSE, NULL);
	sem_available = CreateSemaphore(NULL, this->size, this->size, NULL);
	sem_unavailable = CreateSemaphore(NULL, 0, this->size, NULL);
}

BC_Buffer::~BC_Buffer()
{
	int i;
	for(i = first; i < last; i++)
		free(buffer[i % size]);
	free(buffer);
	CloseHandle(mutex_lock);
	CloseHandle(sem_available);
	CloseHandle(sem_unavailable);
}

void BC_Buffer::insert(void *item)
{
	
	WaitForSingleObject(sem_available, INFINITE);
	this->insert_internal(item);
	ReleaseSemaphore(sem_unavailable, 1, NULL);
}

void BC_Buffer::insert_internal(void *item)
{
	int f, l;
	char *event = (char*) calloc(60, sizeof(char));
	WaitForSingleObject(mutex_lock, INFINITE);
	buffer[last % size] = item;
	last++;
	f = first;
	l = last;
	ReleaseMutex(mutex_lock);
	sprintf_s(event, 59, "Buffer: %d inserted, l - f: %d, f: %d, l: %d", *(int*)item, l - f, f, l);
	logger->log_event(event);
	free(event);
}

void *BC_Buffer::remove()
{
	WaitForSingleObject(sem_unavailable, INFINITE);
	void *item = this->remove_internal();
	ReleaseSemaphore(sem_available, 1, NULL);

	return item;
}

void *BC_Buffer::remove_internal()
{
	int f, l;
	void *item;
	char *event = (char*) calloc(60, sizeof(char));
	WaitForSingleObject(mutex_lock, INFINITE);
	item = buffer[first % size];
	buffer[first % size] = NULL;
	first++;
	f = first;
	l = last;
	ReleaseMutex(mutex_lock);
	sprintf_s(event, 59, "Buffer: %d removed, l - f: %d, f: %d, l: %d", *(int*)item, l - f, f, l);
	logger->log_event(event);
	free(event);

	return item;
}

