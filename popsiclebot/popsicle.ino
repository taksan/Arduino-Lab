#include <Servo.h>
#define Servo Servo
#include "Tickable.h"
#include "feedback.h"
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
