/**
 * @file BC_Logger.cpp 
 * @author Brett Crawford
 * @brief A shared, event logging class
 * @details
 *  Course: CIS 3207, Sec 2
 *  Prof: Kwatny
 *  TAs: Liang and Casey
 *  Date: 2014-10-18
 *  Description: A shared, event logging class. This class is written for 
 *  use with windows.
*/

#include "BC_Logger.hpp"

/**
 * Constructs a shared, event logger object. 
 * 
 * @param[in] log_file The name of the log file in which to record events
*/
BC_Logger::BC_Logger(const char log_file[])
{
	fopen_s(&lfp, log_file, "a");
	mutex_lock = CreateMutex(NULL, FALSE, NULL);
}

/**
 * Destroys a shared, event logger object. 
*/
BC_Logger::~BC_Logger()
{
	fclose(lfp);
	CloseHandle(mutex_lock);
}

/**
 * Records an event within the log. The event can be at most 200 characters.
 *
 * @param[in] event The event to be logged
 * @param Returns 1 on success, otherwise 0
*/int BC_Logger::log_event(const char event[])
{
	/* String to hold date and time (date/time string) */
	char *dts = (char*) calloc(25, sizeof(char));
	/* String to hold date, time, microseconds, and event (full string) */
	int fs_size = 215;
	char *fs = (char*) calloc(fs_size, sizeof(char));

	/* Get time and date */
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);

	sprintf_s(
		dts, 
		25, 
		"%d-%02d-%02d %02d:%02d:%02d:%03d ", 
		systemtime.wYear,
		systemtime.wMonth,
		systemtime.wDay,
		systemtime.wHour,
		systemtime.wMinute,
		systemtime.wSecond,
		systemtime.wMilliseconds);

	/* Build the string to insert in log file */
	strcpy_s(fs, fs_size, dts);
	strcat_s(fs, fs_size, event);
	strcat_s(fs, fs_size, "\n");

	/* Write event to log file */
	WaitForSingleObject(mutex_lock, INFINITE);
	/** CRITICAL SECTION ENTRY */
	fwrite(fs, sizeof(char), strlen(fs), lfp);
	/** CRITICAL SECTION EXIT */
	ReleaseMutex(mutex_lock);

	/* Free all dynamically allocated memory */
	free(dts);
	free(fs);

	// TODO: handle any possible errors
	return 1;
}

