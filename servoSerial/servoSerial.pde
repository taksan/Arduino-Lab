#include <Servo.h>

Servo horiz;
int horizPos=90;

void printServoPos(char id[3], int pos);

void setup()  {
	Serial.begin(9600);
	horiz.attach(7);
	horiz.write(horizPos);
}

void adjustServoPos(Servo * servo, char id[3], int * currentServoPos)
{
	if(Serial.available()==0)
		return;

	int newAngle = Serial.read();

	*currentServoPos = newAngle;
	servo->write(newAngle);
	printServoPos(id, *currentServoPos);
}

void loop()  {
	adjustServoPos(&horiz, "angle", &horizPos);
} 

void printServoPos(char id[3], int pos) {
	char val[12];
	sprintf(val, "%s %04d=", id, pos);
	Serial.print(val);
}
