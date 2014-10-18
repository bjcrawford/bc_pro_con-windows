/* File: BC_Consumer.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

using namespace std;

#include "BC_Consumer.hpp"

BC_Consumer::BC_Consumer(int id, BC_Buffer *buffer, BC_Logger *logger)
{
	this->id = id;
	this->buffer = buffer;
	this->logger = logger;
}

BC_Consumer::~BC_Consumer()
{

}

void BC_Consumer::consume()
{
	char *event = (char*) calloc(60, sizeof(char));
	void *item = buffer->remove();
	sprintf_s(event, 59, "Consumer %d: %d removed from buffer", this->id, *(int*)item);
	logger->log_event(event);
	free(event);
}

