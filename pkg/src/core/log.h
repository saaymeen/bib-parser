#ifndef TUCSE_BIB_PARSER_LOG_H
#define TUCSE_BIB_PARSER_LOG_H

#include <string>
#include <time.h>
#include <iostream>
#include <cstring>

#define BIB_PARSER_NO_LOG 0x00
#define BIB_PARSER_ERROR_LOG 0x01
#define BIB_PARSER_INFO_LOG 0x02
#define BIB_PARSER_DEBUG_LOG 0x03

// Diable logging if not explicitly enabled
#ifndef BIB_PARSER_LOG_LEVEL
#define BIB_PARSER_LOG_LEVEL BIB_PARSER_NO_LOG
#endif

namespace
{
	static inline char *currentTime()
	{
		static char buffer[64];
		time_t rawTime;
		struct tm *timeInfo;

		time(&rawTime);
		timeInfo = localtime(&rawTime);

		strftime(buffer, 64, "%H:%M:%S", timeInfo);

		return buffer;
	}
} // namespace

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define BIB_PARSER_PRINT(format, ...) fprintf(stderr, format, ##__VA_ARGS__)

#define BIB_PARSER_LOG_FORMAT "%s | %-10s | %-15s | %-20s:%d | "
#define BIB_PARSER_VERBOSE_LOG_FORMAT "%s | %-10s | "

#define LOG_ARGS(LOG_TAG) currentTime(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

#define NEWLINE "\n"

#define ERROR_TAG "ERROR"
#define INFO_TAG "INFO"
#define DEBUG_TAG "DEBUG"

#if BIB_PARSER_LOG_LEVEL >= BIB_PARSER_DEBUG_LOG
#define LOG_DEBUG(message, ...) BIB_PARSER_PRINT(BIB_PARSER_LOG_FORMAT message NEWLINE, LOG_ARGS(DEBUG_TAG), ##__VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if BIB_PARSER_LOG_LEVEL >= BIB_PARSER_INFO_LOG
#define LOG_INFO(message, ...) BIB_PARSER_PRINT(BIB_PARSER_LOG_FORMAT message NEWLINE, LOG_ARGS(INFO_TAG), ##__VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if BIB_PARSER_LOG_LEVEL >= BIB_PARSER_ERROR_LOG
#define LOG_ERROR(message, ...) BIB_PARSER_PRINT(BIB_PARSER_LOG_FORMAT message NEWLINE, LOG_ARGS(ERROR_TAG), ##__VA_ARGS__)
#else
#define LOG_ERROR(message, ...)
#endif

#define VERBOSE_LOG(condition, message, ...)                                                                         \
	if (condition)                                                                                                   \
		BIB_PARSER_PRINT(BIB_PARSER_VERBOSE_LOG_FORMAT message NEWLINE, currentTime(), "BIB Parser", ##__VA_ARGS__); \
	else if (BIB_PARSER_LOG_LEVEL)                                                                                   \
	BIB_PARSER_PRINT(BIB_PARSER_LOG_FORMAT message NEWLINE, LOG_ARGS("BIB Parser"), ##__VA_ARGS__)

#endif // TUCSE_BIB_PARSER_LOG_H