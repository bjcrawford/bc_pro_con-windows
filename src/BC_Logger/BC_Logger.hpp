/**
 * @file BC_Logger.hpp
 * @author Brett Crawford
 * @brief A shared, event logging class header
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: The header for the logger class.
*/


#ifndef BC_LOGGER_HPP_
#define BC_LOGGER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
 * A shared, event logging class
*/
class BC_Logger
{
	private:
		FILE *lfp;           /**< A file pointer to the log file */
		HANDLE mutex_lock;   /**< Mutual exclusion lock */

	public:
		BC_Logger(const char[]);
		virtual ~BC_Logger();

		int log_event(const char[]);
};

#endif /* BC_LOGGER_HPP_ */
