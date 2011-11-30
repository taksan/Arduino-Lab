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

