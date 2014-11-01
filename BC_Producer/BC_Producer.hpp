/**
 * @file BC_Producer.hpp
 * @author Brett Crawford
 * @brief A producer class header
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: The header for the producer class.
*/

#ifndef BC_PRODUCER_HPP_
#define BC_PRODUCER_HPP_

#include <random>
#include <stdlib.h>
#include <windows.h>

#include "../BC_Buffer/BC_Buffer.hpp"
#include "../BC_Logger/BC_Logger.hpp"
 
/** 
 * A producer class to be used with an implementation of the producer/consumer 
 * problem. The producer class is to be used in conjunction with a shared 
 * buffer and a shared logger as well as with other producers and consumers.
*/
class BC_Producer
{
	private:
		int id;              /**< An identifier for the producer */
		BC_Buffer *buffer;   /**< A pointer to the shared buffer */
		BC_Logger *logger;   /**< A pointer to the shared logger */

	public:
		BC_Producer(int id, BC_Buffer*, BC_Logger*);
		virtual ~BC_Producer();

		void produce();
};

#endif /* BC_PRODUCER_HPP_ */
