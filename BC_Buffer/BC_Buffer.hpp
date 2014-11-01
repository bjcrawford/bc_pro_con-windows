/**
 * @file BC_Buffer.hpp
 * @author Brett Crawford
 * @brief A shared, bounded buffer class header
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: The header for the buffer class.
*/

#ifndef BC_BUFFER_HPP_
#define BC_BUFFER_HPP_

#include <stdlib.h>
#include <string>
#include <windows.h>

#include "../BC_Logger/BC_Logger.hpp"

/**
 * A shared, bounded buffer class to be used with an implementation of the 
 * producer/consumer problem. The buffer class is to be used in conjunction 
 * with a shared logger as well as with producers and consumers. The buffer
 * will store elements of the type void* meaning the elements should be 
 * allocated on the heap before insertion into the buffer. Any elements 
 * not removed from the buffer before it is destroyed will be freed.
*/ 
class BC_Buffer
{
	private:
		size_t firstFilled;      /**< The index of the first filled slot */
		size_t nextEmpty;        /**< The index of the next empty slot */
		size_t size;             /**< The max number of elements */
		size_t visual;           /**< A flag to visualize buffer in event log */
		void **buffer;           /**< An array of void pointers */
		BC_Logger *logger;       /**< A pointer to the shared logger */
		HANDLE mutex_lock;       /**< Mutex lock for buffe access */
		HANDLE sem_available;    /**< Number of available slots in buffer */
		HANDLE sem_unavailable;  /**< Number of unavailable slots in buffer */

		std::string getBufferStr();

	public:
		BC_Buffer(size_t, BC_Logger*, size_t);
		virtual ~BC_Buffer();

		void insert(void*);
		void *remove();
};

#endif /* BC_BUFFER_HPP_ */
