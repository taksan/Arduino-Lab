#include <Servo.h>
#define SERVO_PIN 9
#define POT 8

Servo servo;

void setup()
{
	Serial.begin(9600);
	servo.attach(SERVO_PIN);
}

int previousAngle = -1;
void loop()
{
	int pot = analogRead(POT);
	int angle = map(pot, 0, 1024, 0, 180);//180.0/1024 * pot;
	servo.write(angle);
}
