#include <Servo.h>
#define SERVO_PIN 7
#define SERVO2_PIN 8
#define POT1 4
#define POT2 5

Servo servo[2];
int potPin[2] = {POT1, POT2};

void setup()
{
	Serial.begin(9600);
	servo[0].attach(SERVO_PIN);
	servo[1].attach(SERVO2_PIN);
}

int previousAngle[2] = {-1,-1};
void updateAngle(int servoNum) {
	int pot = analogRead(potPin[servoNum]);
	int angle = map(pot, 0, 1024, 0, 180);//180.0/1024 * pot;
	if (previousAngle[servoNum] != angle) {
		Serial.println(angle, DEC);
		servo[servoNum].write(angle);
	}
	previousAngle[servoNum] = angle;
}

void loop() {
	updateAngle(0);
	updateAngle(1);
}
