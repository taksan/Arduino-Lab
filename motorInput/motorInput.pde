#include <Servo.h>
#include "MotorDial.h"

#define SERVO_PIN 9

MotorDial motorDial = MotorDial(5,6,7);
Servo servo;
int motorAngle;

void setup()
{
	Serial.begin(9600);
	servo.attach(SERVO_PIN);
	motorAngle = servo.read();
}

void loop()
{
	MotorDial::Direction direction = motorDial.turnDirection();
	if (direction == MotorDial::none)
		return;

	if (direction == MotorDial::clockwise) {
		Serial.println("turned clockwise");
		motorAngle-=2;
		if (motorAngle < 0)
			motorAngle = 0;

	}
	else {
		Serial.println("turned counter-clockwise");
		motorAngle+=2;
		if (motorAngle > 180)
			motorAngle = 180;
	}
	servo.write(motorAngle);
}
