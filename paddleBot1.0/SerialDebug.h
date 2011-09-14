#ifndef SERIAL__DEBUG__H__
#define SERIAL__DEBUG__H__

#include <stdarg.h>
#ifndef CPPUNIT_TEST_SUITE


class SerialDebug {
public:
	static void println(const char * fmt, ...) 
	{
		va_list args;
		va_start(args, fmt);
		char msg[80];
		vsprintf(msg, fmt, args);
		va_end(args);
		Serial.println(msg);
	}
};
#else
class SerialDebug {
public:
	static void println(const char * fmt, ...) 
	{
		va_list args;
		va_start(args, fmt);
		char msg[80];
		vsprintf(msg, fmt, args);
		va_end(args);

		printf("%s\n", msg);
	}
};


#endif

#endif
