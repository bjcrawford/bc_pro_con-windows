/* File: BC_Pro_Con.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

#include "BC_Buffer/BC_Buffer.hpp"
#include "BC_Consumer/BC_Consumer.hpp"
#include "BC_Logger/BC_Logger.hpp"
#include "BC_Producer/BC_Producer.hpp"

#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

#define BUFFER_SIZE 20

const char log_file[] = "log.txt";

void pro_con_solution();
DWORD WINAPI produce(LPVOID);
DWORD WINAPI consume(LPVOID);

int main(int argc, char **argv)
{
	pro_con_solution();
	return EXIT_SUCCESS;
}

void pro_con_solution()
{
	printf("Main thread Start\n");
	int i;
	BC_Logger *logger;
	BC_Buffer *buffer;
	BC_Producer *producer[4];
	BC_Consumer *consumer[3];

	DWORD producer_threads_ids[4];
	DWORD consumer_threads_ids[3];

	HANDLE producer_threads[4];
	HANDLE consumer_threads[3];

	logger = new BC_Logger(log_file);
	buffer = new BC_Buffer(BUFFER_SIZE, logger);

	for(i = 0; i < 4; i++)
		producer[i] = new BC_Producer(i, buffer, logger);
	
	for(i = 0; i < 3; i++)
		consumer[i] = new BC_Consumer(i, buffer, logger);
	
	for(i = 0; i < 4; i++)
	{
		Sleep(10);
		producer_threads[i] = CreateThread(NULL, 0, produce, producer[i], 0, &producer_threads_ids[i]);
	}

	for(i = 0; i < 3; i++)
	{
		Sleep(10);
		consumer_threads[i] = CreateThread(NULL, 0, consume, consumer[i], 0, &consumer_threads_ids[i]);
	}

	WaitForMultipleObjects(4, producer_threads, TRUE, INFINITE);

	WaitForMultipleObjects(3, consumer_threads, TRUE, INFINITE);

	delete(logger);
	delete(buffer);

	for(i = 0; i < 4; i++)
		delete(producer[i]);

	for(i = 0; i < 3; i++)
		delete(consumer[i]);

	printf("Main thread finished\n");
}

DWORD WINAPI produce(LPVOID producer)
{
	int i;
	for(i = 0; i < 20; i++)
	{
		Sleep(50);
		((BC_Producer*) producer)->produce();
	}

	return 0;
}

DWORD WINAPI consume(LPVOID consumer)
{
	int i;
	for(i = 0; i < 25; i++)
	{
		Sleep(50);
		((BC_Consumer*) consumer)->consume();
	}

	return 0;
}
