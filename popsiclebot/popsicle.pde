#include <ServoTimer2.h>
#define Servo ServoTimer2

#include "Robot.h"

class Controller {
public:
	int available() {
		return Serial.available();
	}

	char * readCommand() {
		char cmd[20];
		int i=0;
		while(Serial.available()) {
			char data = Serial.read();
			cmd[i]=data;
			if (data == '\n') break;
			i++;
		}
		cmd[i] = 0;
		return strdup(cmd);
	}
};

Controller controller;
Robot * robot;

void setup()
{
	Serial.begin(9600);
	robot = new Robot();
}

void loop()
{
	if (controller.available()) {
		char * command = controller.readCommand();
		robot->processCommand(command);
		free(command);
	}
}
