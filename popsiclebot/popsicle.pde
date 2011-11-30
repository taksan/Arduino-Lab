#include <ServoTimer2.h>
#define Servo ServoTimer2

#include "Robot.h"

Controller controller;
Robot * robot;

void setup()
{
	Serial.begin(9600);
	robot = new Robot(&controller);
}

void loop()
{
	if (controller.available()) {
		char * command = controller.readCommand();
		robot->processCommand(command);
		free(command);
	}
}
