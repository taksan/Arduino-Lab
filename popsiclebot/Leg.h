#include "ArticulatedJoint.h"

class Leg : public Tickable {
protected:
	ArticulatedJoint _shoulder;
	ArticulatedJoint _upper;
	ArticulatedJoint _knee;
	ArticulatedJoint _foot;
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
	}

	void init (int shoulder, int upper, int knee, int foot) {
		_shoulder.write(shoulder);
		_upper.write(upper);
		_knee.write(knee);
		_foot.write(foot);
	}

	void tick() {
		_shoulder.tick();
		_upper.tick();
		_knee.tick();
		_foot.tick();
	}

	virtual bool shoulder(int angle) {
		return _shoulder.rotate(angle);
	}
	virtual bool upper(int angle) {
		return _upper.rotate(angle);
	}
	virtual bool knee(int angle) {
		return _knee.rotate(angle);
	}
	virtual bool foot(int angle) {
		return _foot.rotate(angle);
	}

	int shoulder() {
		return _shoulder.read();
	}
	int upper() {
		return _upper.read();
	}
	int knee() {
		return _knee.read();
	}
	int foot() {
		return _foot.read();
	}
};

class LeftLeg : public Leg {
public:
	LeftLeg(FeedbackCallback * feedback, int shoulderPin, int upperPin, int kneePin, int footPin) :
		Leg(feedback, shoulderPin, upperPin, kneePin, footPin,
			50,160,
			70,180,
			0, 180)
	{
	}
};

class RightLeg : public Leg {
public:
	RightLeg(FeedbackCallback * feedback, int shoulderPin, int upperPin, int kneePin, int footPin):
		Leg(feedback, shoulderPin, upperPin, kneePin, footPin, 
		50, 160,
		0, 180,
		0, 180)
	{
	}
};
