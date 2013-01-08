//#include <Servo.h>
/*
Servo horiz, vert;
int horizPos=90, vertPos=90;
*/

void setup()  {
	/*
	Serial.begin(9600);
	horiz.attach(7);
	vert.attach(8);

	horiz.write(horizPos);
	vert.write(vertPos);
	*/

	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);

	digitalWrite(3, LOW);
	digitalWrite(9, LOW);
}

void loop()  {
} 
