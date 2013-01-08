#include <Servo.h>

Servo horiz, vert;
int horizPos=90, vertPos=90;

void setup()  {
	Serial.begin(9600);
	horiz.attach(7);
	vert.attach(8);

	horiz.write(horizPos);
	vert.write(vertPos);
}

void loop()  {
} 
