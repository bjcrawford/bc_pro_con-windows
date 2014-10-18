/* File: BC_Producer.h
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

#ifndef BC_PRODUCER_H_
#define BC_PRODUCER_H_

#include <stdlib.h>
#include <time.h>

#include "../BC_Buffer/BC_Buffer.hpp"
#include "../BC_Logger/BC_Logger.hpp"

class BC_Producer
{
	private:
		int id;
		BC_Buffer *buffer;
		BC_Logger *logger;

	public:
		BC_Producer(int id, BC_Buffer*, BC_Logger*);
		virtual ~BC_Producer();

		void produce();
};

#endif /* BC_PRODUCER_H_ */
