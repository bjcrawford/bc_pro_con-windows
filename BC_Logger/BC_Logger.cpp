/* File: BC_Logger.cpp
   Author: Brett Crawford
   Date: 2014-
   Prof: Kwatny
   TAs: Liang and Casey
   Course: CIS 3207, Sec 2
   Description:
*/

using namespace std;

#include "BC_Logger.hpp"

BC_Logger::BC_Logger(const char log_file[])
{
	fopen_s(&lfp, log_file, "a");
	mutex_lock = CreateMutex(NULL, FALSE, NULL);
}

BC_Logger::~BC_Logger()
{
	fclose(lfp);
	CloseHandle(mutex_lock);
}

int BC_Logger::log_event(const char event[])
{
	/* String to hold date and time (date and time string) */
	char *pDts = (char*) calloc(25, sizeof(char));
	/* String to hold date, time, microseconds, and event (full string) */
	int pFs_size = 25 + strlen(event) + 1;
	char *pFs = (char*) calloc(pFs_size, sizeof(char));

	/* Get time and date */
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);

	sprintf_s(
		pDts, 
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
	strcpy_s(pFs, pFs_size, pDts);
	strcat_s(pFs, pFs_size, event);
	strcat_s(pFs, pFs_size, "\n");

	/* Write event to log file */
	WaitForSingleObject(mutex_lock, INFINITE);
	fwrite(pFs, sizeof(char), strlen(pFs), lfp);
	ReleaseMutex(mutex_lock);

	/* Free all dynamically allocated memory */
	free(pDts);
	free(pFs);

	// TODO: handle any possible errors
	return 1;
}

