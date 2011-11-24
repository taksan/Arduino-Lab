#include <Servo.h>

Servo horiz, vert;
int horizPos=90, vertPos=90;

void printServoPos(char id[3], int pos);

void setup()  {
	Serial.begin(9600);
	horiz.attach(7);
	vert.attach(8);

	horiz.write(horizPos);
	vert.write(vertPos);
}

void adjustServoPos(Servo * servo, char id[3], int * currentServoPos)
{
	if(Serial.available()==0)
		return;

	char offset = Serial.read();
	int newPos = *currentServoPos + offset;
	if (newPos < 0 || newPos > 180) {
		printServoPos(id, *currentServoPos);
		return;
	}
	*currentServoPos = newPos;
	servo->write(newPos);
	printServoPos(id, *currentServoPos);
}

void loop()  {
	adjustServoPos(&horiz, "hz", &horizPos);
} 

void printServoPos(char id[3], int pos) {
	char val[9];
	sprintf(val, "%s:%04d=", id, pos);
	Serial.print(val);
}
