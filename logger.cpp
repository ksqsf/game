#include <cstdio>
#include <cstdarg>
#include <ctime>
#include "logger.h"
using namespace std;

#define MAXLINE 4096
static const char *get_desc(LogLevel level);
static void log_do(LogLevel level, const char *fmt, va_list ap);

void log_fatal(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	log_do(LogLevel::Fatal, fmt, ap);
	va_end(ap);
}

void log_error(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	log_do(LogLevel::Error, fmt, ap);
	va_end(ap);
}

void log_info(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	log_do(LogLevel::Info, fmt, ap);
	va_end(ap);
}

void log_debug(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	log_do(LogLevel::Debug, fmt, ap);
	va_end(ap);
}

static const char *get_desc(LogLevel level)
{
	switch (level) {
	case LogLevel::Debug: return "debug";
	case LogLevel::Info:  return "info";
	case LogLevel::Error: return "error";
	case LogLevel::Fatal: return "fatal";
	}
}

/* length of a message cannot exceed MAXLINE */
static void log_do(LogLevel level, const char *fmt, va_list ap)
{
	char logbuf[MAXLINE];
	char timebuf[100];
	time_t t = time(nullptr);
	
	vsnprintf(logbuf, MAXLINE, fmt, ap);
	if (strftime(timebuf, sizeof(timebuf), "%c", localtime(&t))) {
		fprintf(stderr, "[%s] - %s - %s", get_desc(level), timebuf, logbuf);
	} else {
		fprintf(stderr, "[%s] - (time?) - %s", get_desc(level), logbuf);
	}
	fflush(stderr);
}
