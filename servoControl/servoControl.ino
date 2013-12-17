#include<Servo.h>
#include "../serialReader/SerialReader.h"

#define MIN 20
#define MAX 150

SerialReader controller;
Servo servo;
int angle = MAX;
char str[30];

void setup()  {
	Serial.begin(9600);
	servo.attach(8);
}

void loop()  {
	if (controller.available() > 0) {
		char * cmd = controller.readCommand();
		if (cmd[0]=='L') {
			angle+=5;
		}
		else
		if (cmd[0]=='R') {
			angle-=5;
		}
		if (angle<MIN)
			angle = MIN;
		if (angle>MAX)
			angle = MAX;

		sprintf(str,"new angle: %d\n",angle);
		Serial.write(str);

		free(cmd);
	}
	servo.write(angle);
} 

