/* File: BC_Buffer.h
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

#ifndef BC_BUFFER_H_
#define BC_BUFFER_H_

#include <stdlib.h>
#include <windows.h>

#include "../BC_Logger/BC_Logger.hpp"

class BC_Buffer
{
	private:
		size_t first;
		size_t last;
		size_t size;
		void **buffer;
		BC_Logger *logger;

		HANDLE mutex_lock;    /* Mutual exclusion lock */

		HANDLE sem_available;         /* Number of available slots in buffer */
		HANDLE sem_unavailable;       /* Number of unavailable slots in buffer */

		void insert_internal(void*);
		void *remove_internal();

	public:
		BC_Buffer(size_t, BC_Logger*);
		virtual ~BC_Buffer();

		int isFull();
		int isEmpty();
		void insert(void*);
		void *remove();
};

#endif /* BC_BUFFER_H_ */
