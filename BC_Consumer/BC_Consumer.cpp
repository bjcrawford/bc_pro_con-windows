/**
 * @file BC_Consumer.cpp
 * @author Brett Crawford
 * @brief A consumer class
 * @details 
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: A consumer class to be used with an implementation of the 
 *  producer/consumer problem. The consumer class is to be used in conjunction
 *  with a shared buffer and a shared logger as well as with other producers
 *  and consumers. This class is written for use with windows.
*/

using namespace std;

#include "BC_Consumer.hpp"

/**
 * Constructs a consumer object. 
 * 
 * @param[in] id An identifer for the consumer
 * @param[in] buffer A pointer to the shared buffer
 * @param[in] logger A pointer to the shared logger
*/
BC_Consumer::BC_Consumer(int id, BC_Buffer *buffer, BC_Logger *logger)
{
	this->id = id;
	this->buffer = buffer;
	this->logger = logger;
}

/**
 * Destroys a consumer object
*/
BC_Consumer::~BC_Consumer()
{
	this->buffer = NULL;
	this->logger = NULL;
}

/**
 * Consumes pointer from the buffer, logs the event with the logger, and 
 * releases the memory used by the pointer.
*/
void BC_Consumer::consume()
{
	char *event = (char*) calloc(65, sizeof(char));
	void *item = buffer->remove();
	sprintf_s(event, 65, "Consumer %d: %d removed from buffer", this->id, *(int*)item);
	logger->log_event(event);
	free(event);
}

