/* File: BC_Consumer.h
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

#ifndef BC_CONSUMER_H_
#define BC_CONSUMER_H_

#include "../BC_Buffer/BC_Buffer.hpp"
#include "../BC_Logger/BC_Logger.hpp"

class BC_Consumer
{
	private:
		int id;
		BC_Buffer *buffer;
		BC_Logger *logger;

	public:
		BC_Consumer(int, BC_Buffer*, BC_Logger*);
		virtual ~BC_Consumer();

		void consume();
};

#endif /* BC_CONSUMER_H_ */
