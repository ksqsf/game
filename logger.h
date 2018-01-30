#pragma once

enum class LogLevel
{
	Fatal,
	Error,
	Info,
	Debug
};

void log_fatal(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_debug(const char *fmt, ...);

#define ENTER_FUNC log_debug("Entering %s\n", __FUNC__)
#define LEAVE_FUNC log_debug("Leaving %s\n", __FUNC__)
