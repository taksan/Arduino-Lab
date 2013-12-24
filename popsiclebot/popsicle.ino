#include "../serialReader/SerialReader.h"
#include <Servo.h>
#define Servo Servo

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

#include "Robot.h"

FeedbackCallback feedback;
Robot * robot;
char accumulatedCmd[30];

void setup()
{
	Serial.begin(9600);
	robot = new Robot(&feedback);
	accumulatedCmd[0] = 0;
}

void loop()
{
	if (feedback.available()) {
		char * command = feedback.readCommand();

		if (command[strlen(command)-1] == '$') {
			strcat(accumulatedCmd, command);
			accumulatedCmd[strlen(accumulatedCmd)-1]=0;
			robot->processCommand(accumulatedCmd);
			accumulatedCmd[0] = 0;
		}
		else {
			strcat(accumulatedCmd, command);
		}
		free(command);
	}
}
