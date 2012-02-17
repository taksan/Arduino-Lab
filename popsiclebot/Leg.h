class Leg {
protected:
	Servo _shoulder;
	Servo _upper;
	Servo _knee;
	Servo _foot;
public:
	Leg(int shoulderPin, int upperPin, int kneePin, int footPin) {
		_shoulder.attach(shoulderPin);
		_upper.attach(upperPin);
		_knee.attach(kneePin);
		_foot.attach(footPin);

		shoulder(90);
		upper(90);
		knee(90);
		foot(90);
	}

	virtual void shoulder(int angle) {
		_shoulder.write(angle);
	}

	virtual void upper(int angle) {
		_upper.write(angle);
	}

	virtual void knee(int angle) {
		_knee.write(angle);
	}

	virtual void foot(int angle) {
		_foot.write(angle);
	}
};

class LeftLeg : public Leg {
public:
	LeftLeg(int shoulderPin, int upperPin, int kneePin, int footPin) :
		Leg(shoulderPin, upperPin, kneePin, footPin)
	{
	}

};

class RightLeg : public Leg {
public:
	RightLeg(int footPin, int kneePin, int upperPin, int shoulderPin):
		Leg(shoulderPin, upperPin, kneePin, footPin)
	{
	}
	void shoulder(int angle) {
		Leg::shoulder(180-angle);
	}

	void upper(int angle) {
		Leg::upper(180-angle);
	}

	void knee(int angle) {
		Leg::knee(180-angle);
	}

	void foot(int angle) {
		Leg::foot(180-angle);
	}
};

