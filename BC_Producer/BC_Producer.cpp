/* File: BC_Producer.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

using namespace std;

#include "BC_Producer.hpp"

BC_Producer::BC_Producer(int id, BC_Buffer *buffer, BC_Logger *logger)
{
	this->id = id;
	this->buffer = buffer;
	this->logger = logger;
}

BC_Producer::~BC_Producer()
{

}

void BC_Producer::produce()
{
	char *event = (char*) calloc(65, sizeof(char));
	int *item = (int*) calloc(1, sizeof(int));
	srand(clock() * time(NULL));
	*item = rand() % 10000;
	buffer->insert((void*) item);
	sprintf_s(event, 65, "Producer %d: %d inserted into buffer", this->id, *item);
	logger->log_event(event);
	free(event);
}

