#include <Servo.h>

Servo horiz, vert;
int horizPos=90, vertPos=90;

void printServoPos(char id[3], int pos);
void adjustServoPos(Servo * servo, char id[3], int * currentServoPos);

void setup()  {
	Serial.begin(9600);
	horiz.attach(7);
	vert.attach(8);

	horiz.write(horizPos);
	vert.write(vertPos);
}

void loop()  {
	adjustServoPos(&horiz, "hz", &horizPos);
	adjustServoPos(&vert, "vt", &vertPos);
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
//	int inc=1;
//	if (*currentServoPos > newPos)
//		inc=-1;
//	for(;*currentServoPos!=newPos; *currentServoPos+=inc) {
//		servo->write(*currentServoPos);
//	}
	printServoPos(id, *currentServoPos);
	*currentServoPos = newPos;
	servo->write(*currentServoPos);
}

void printServoPos(char id[3], int pos) {
	char val[9];
	sprintf(val, "%s:%04d=", id, pos);
}
