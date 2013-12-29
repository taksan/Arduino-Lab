#ifndef __FEEDBACK_H_
#define __FEEDBACK_H_
#include "../serialReader/SerialReader.h"

class FeedbackCallback : public SerialReader {
public:
	void printf(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		char out[100];
		vsprintf(out, fmt, args);
		Serial.print(out);
		va_end(args);
	}

};

#endif
