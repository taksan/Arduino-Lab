#define NUNCHUCK_RX_PIN 7
#include <ServoTimer2.h>
#define Servo ServoTimer2

int8_t currentGameNumber;

class Leg {
protected:
	Servo _upper;
	Servo _middle;
	Servo _knee;
public:
	Leg(int upperPin, int middlePin, int kneePin) {
		_upper.attach(upperPin);
		_middle.attach(middlePin);
		_knee.attach(kneePin);

		upper(90);
		middle(90);
		knee(90);
	}

	virtual void upper(int angle) {
		_upper.write(angle);
	}

	virtual void middle(int angle) {
		_middle.write(angle);
	}

	virtual void knee(int angle) {
		_knee.write(angle);
	}
};

class LeftLeg : public Leg {
public:
	LeftLeg(int upperPin, int middlePin, int kneePin) :
		Leg(upperPin, middlePin, kneePin)
	{
	}

};

class RightLeg : public Leg {
public:
	RightLeg(int upperPin, int middlePin, int kneePin) :
		Leg(upperPin, middlePin, kneePin)
	{
	}
	void upper(int angle) {
		_upper.write(180-angle);
	}

	void middle(int angle) {
		_middle.write(180-angle);
	}

	void knee(int angle) {
		_knee.write(180-angle);
	}

};

LeftLeg * left;
RightLeg * right;

void setup()
{
	Serial.begin(9600);
	Serial.println("------o---- starting");
	left = new LeftLeg(8,9,10);
	right = new RightLeg(11,12,13);


	left->upper(60);
	left->knee(45);

	right->knee(45);
}

void loop()
{
}
