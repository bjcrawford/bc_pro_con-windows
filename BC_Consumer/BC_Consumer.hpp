/**
 * @file BC_Consumer.hpp
 * @author Brett Crawford
 * @brief A consumer class header
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: The header for the consumer class.
*/

#ifndef BC_CONSUMER_H_
#define BC_CONSUMER_H_

#include "../BC_Buffer/BC_Buffer.hpp"
#include "../BC_Logger/BC_Logger.hpp"

/**  
 * A consumer class to be used with an implementation of the producer/consumer 
 * problem. The consumer class is to be used in conjunction with a shared 
 * buffer and a shared logger as well as with other producers and consumers.
*/
class BC_Consumer
{
	private:
		int id;              /**< An identifier for the producer */
		BC_Buffer *buffer;   /**< A pointer to the shared buffer */
		BC_Logger *logger;   /**< A pointer to the shared logger */

	public:
		BC_Consumer(int, BC_Buffer*, BC_Logger*);
		virtual ~BC_Consumer();

		void consume();
};

#endif /* BC_CONSUMER_H_ */
