class LegJoint : public Servo {
	FeedbackCallback * feedback;
	int lowerBound;
	int upperBound;
public:
	LegJoint(FeedbackCallback * feedback, int lower, int upper):
		feedback(feedback), 
		lowerBound(lower),upperBound(upper) 
	{
	}

	bool accept(int value) {
		return (value >= lowerBound && value <= upperBound);
	}

	bool write(int value) {
		if (!accept(value)) {
			feedback->printf("%d rejected because it is out of allowed bounds\n", value);
			return false;
		}

		Servo::write(value);
		return true;
	}
};

class Leg {
protected:
	LegJoint _shoulder;
	LegJoint _upper;
	LegJoint _knee;
	LegJoint _foot;
public:
	Leg(FeedbackCallback * feedback, int shoulderPin, int upperPin, int kneePin, int footPin, 
		int upperLowBound, int upperUpBound,
		int kneeLowBound, int kneeUpBound,
		int footLowBound, int footUpBound):
			_shoulder(feedback, 0, 180),
			_upper(feedback, upperLowBound, upperUpBound),
			_knee(feedback, kneeLowBound, kneeUpBound),
			_foot(feedback, footLowBound, footUpBound)
	{
		_shoulder.attach(shoulderPin);
		_upper.attach(upperPin);
		_knee.attach(kneePin);
		_foot.attach(footPin);

		shoulder(90);
		upper(90);
		knee(90);
		foot(90);
	}

	virtual bool shoulder(int angle) {
		return _shoulder.write(angle);
	}

	virtual bool upper(int angle) {
		return _upper.write(angle);
	}

	virtual bool knee(int angle) {
		return _knee.write(angle);
	}

	virtual bool foot(int angle) {
		return _foot.write(angle);
	}
};

class LeftLeg : public Leg {
public:
	LeftLeg(FeedbackCallback * feedback, int shoulderPin, int upperPin, int kneePin, int footPin) :
		Leg(feedback, shoulderPin, upperPin, kneePin, footPin,
			55,110,
			70,180,
			90, 180)
	{
	}

};

class RightLeg : public Leg {
public:
	RightLeg(FeedbackCallback * feedback, int footPin, int kneePin, int upperPin, int shoulderPin):
		Leg(feedback, shoulderPin, upperPin, kneePin, footPin, 
		50, 180,
		0, 180,
		85, 180)
	{
	}
	bool shoulder(int angle) {
		return Leg::shoulder(180-angle);
	}

//	void upper(int angle) {
//		Leg::upper(180-angle);
//	}

	bool knee(int angle) {
		return Leg::knee(180-angle);
	}

	bool foot(int angle) {
		return Leg::foot(180-angle);
	}
};
