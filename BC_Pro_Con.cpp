/* File: BC_Pro_Con.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

/** Includes */
#include "BC_Buffer/BC_Buffer.hpp"
#include "BC_Consumer/BC_Consumer.hpp"
#include "BC_Logger/BC_Logger.hpp"
#include "BC_Producer/BC_Producer.hpp"

#include <iostream>
#include <windows.h>
#include <stdio.h>

/** Namespace */
using namespace std;

/** Constants */
#define BUFFER_SIZE 20      /**< Size of the buffer */
#define NUM_PRODUCERS 4     /**< Number of producers */
#define NUM_CONSUMERS 3     /**< Number of consumers */
#define NUM_PRODUCTIONS 20  /**< Number of productions each producer makes */
#define NUM_CONSUMPTIONS 25 /**< Number of consumptions each consumer makes */

/** The name of the log file to be used */
const char log_file[] = "log.txt";

/** A struct to hold the arguments to be passed to the produce function */
typedef struct 
{
	size_t num;             /**< The number of productions to make */
	BC_Producer *producer;  /**< A pointer to the producer object */
} produce_args;

/** A struct to hold the arguments to be passed to the consume function */
typedef struct 
{
	size_t num;             /**< The number of consumptions to make */
	BC_Consumer *consumer;  /**< A pointer to the consumer object */
} consume_args;

/** Function declarations */
DWORD WINAPI produce(LPVOID);
DWORD WINAPI consume(LPVOID);

/**
 * The main function of the solution.
*/
int main(int argc, char **argv)
{
	printf("Main thread start\n");

	/** Declare variable */
	int i;
	BC_Logger *logger;
	BC_Buffer *buffer;
	BC_Producer *producer[NUM_PRODUCERS];
	BC_Consumer *consumer[NUM_CONSUMERS];
	DWORD producer_threads_ids[NUM_PRODUCERS];
	DWORD consumer_threads_ids[NUM_CONSUMERS];
	HANDLE producer_threads[NUM_PRODUCERS];
	HANDLE consumer_threads[NUM_CONSUMERS];

	/** Instantiate logger and buffer objects */
	logger = new BC_Logger(log_file);
	buffer = new BC_Buffer(BUFFER_SIZE, logger);

	/** Instantiate producers */
	for(i = 0; i < NUM_PRODUCERS; i++)
		producer[i] = new BC_Producer(i, buffer, logger);
	
	/** Instantiate consumers */
	for(i = 0; i < NUM_CONSUMERS; i++)
		consumer[i] = new BC_Consumer(i, buffer, logger);
	
	/** Create producer threads */
	for(i = 0; i < NUM_PRODUCERS; i++)
	{
		Sleep(10);
		produce_args *p_args = (produce_args*) calloc(1, sizeof(produce_args));
		p_args->num = NUM_PRODUCTIONS;
		p_args->producer = producer[i];
		producer_threads[i] = CreateThread(NULL, 0, produce, p_args, 0, 
			                               &producer_threads_ids[i]);
		printf("Producer %d thread created\n", i);
	}

	/** Create consumer threads */
	for(i = 0; i < NUM_CONSUMERS; i++)
	{
		Sleep(10);
		consume_args *c_args = (consume_args*) calloc(1, sizeof(consume_args));
		c_args->num = NUM_CONSUMPTIONS;
		c_args->consumer = consumer[i];
		consumer_threads[i] = CreateThread(NULL, 0, consume, c_args, 0, 
			                               &consumer_threads_ids[i]);
		printf("Consumer %d thread created\n", i);
	}

	/** Ensure producer threads finished */
	WaitForMultipleObjects(NUM_PRODUCERS, producer_threads, TRUE, INFINITE);
	printf("All producers finished\n");

	/** Ensure consumer threads finished */
	WaitForMultipleObjects(NUM_CONSUMERS, consumer_threads, TRUE, INFINITE);
	printf("All consumers finished\n");

	/** Clean up */
	delete(logger);
	delete(buffer);
	for(i = 0; i < NUM_PRODUCERS; i++)
		delete(producer[i]);
	for(i = 0; i < NUM_CONSUMERS; i++)
		delete(consumer[i]);

	printf("Main thread finished\n");

	return EXIT_SUCCESS;
}

/**
 * Uses a producer object to perform num productions.
 *
 * @param[in] args A void pointer to a produce_args struct containing 
 *                 the necessary arguments.
*/
DWORD WINAPI produce(LPVOID args)
{
	size_t i;
	produce_args *p_args = (produce_args*) args;
	for(i = 0; i < p_args->num; i++)
	{
		Sleep(50);
		p_args->producer->produce();
	}

	return 0;
}

/**
 * Uses a consumer object to perform num consumptions.
 *
 * @param[in] args A void pointer to a consume_args struct containing 
 *                 the necessary arguments.
*/
DWORD WINAPI consume(LPVOID args)
{
	size_t i;
	consume_args *c_args = (consume_args*) args;
	for(i = 0; i < c_args->num; i++)
	{
		Sleep(50);
		c_args->consumer->consume();
	}

	return 0;
}
