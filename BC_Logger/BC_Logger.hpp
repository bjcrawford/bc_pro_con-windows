/* File: BC_Logger.h
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

#ifndef BC_LOGGER_H_
#define BC_LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

class BC_Logger
{
	private:
		FILE *lfp;
		HANDLE mutex_lock;

	public:
		BC_Logger(const char[]);
		virtual ~BC_Logger();

		int log_event(const char[]);
};

#endif /* BC_LOGGER_H_ */
