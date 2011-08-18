#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "ArduinoApi.h"

class LightFollow {
public:
	LightFollow(int leftEyePin, int rightEyePin, ArduinoApi * api)
	{
		this->leftEyePin = leftEyePin;
		this->rightEyePin = rightEyePin;

		this->baseLeftLevel = api->_analogRead(leftEyePin);
		this->baseRightLevel = api->_analogRead(rightEyePin);

		this->leftRightAdjust = (float)this->baseRightLevel / this->baseLeftLevel;
		this->api = api;
	}

	void update() {
		leftEyeLevel = api->_analogRead(leftEyePin);
		rightEyeLevel = api->_analogRead(rightEyePin);
	}

	bool wentLeft() {
		return  (leftIntensity() > rightIntensity());
	}

	bool wentRight() {
		return  (rightIntensity() > leftIntensity());
	}

private:
	int leftIntensity() {
		return (leftEyeLevel - baseLeftLevel) * leftRightAdjust;
	}

	int rightIntensity() {
		return rightEyeLevel - baseRightLevel;
	}

	int leftEyePin;
	int rightEyePin;

	int leftEyeLevel;
	int rightEyeLevel;

	int baseLeftLevel;
	int baseRightLevel;
	ArduinoApi * api;
	float leftRightAdjust;
};

#endif
