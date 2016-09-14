#include <Servo.h>

Servo horiz, vert;
int horizPos=0, vertPos=0;

void setup()  {
	Serial.begin(9600);
	horiz.attach(9);
	vert.attach(10);

	horiz.write(horizPos);
	vert.write(vertPos);
}

void loop()  {
	delay(10);
	horizPos = (horizPos + 1)%90;
	vertPos = (vertPos + 1)%180;
//	horiz.write(horizPos);
//	vert.write(vertPos);
} 
