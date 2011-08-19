#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "SerialDebug.h"

#include "ArduinoApi.h"

class LightDirectionDetector {
public:
	LightDirectionDetector(int leftEyePin, int rightEyePin, ArduinoApi * api):
		api(api),
		leftEyePin(leftEyePin),
		rightEyePin(rightEyePin)
	{
		this->gaugeBase();

		this->leftRightAdjust = (float)this->baseRightLevel / this->baseLeftLevel;
	}

	void update() {
		leftEyeLevel = api->_analogRead(leftEyePin);
		rightEyeLevel = api->_analogRead(rightEyePin);

		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEyeLevel, rightEyeLevel);
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftIntensity(), rightIntensity());
	}

	bool wentLeft() {
		return  (leftIntensity() > rightIntensity());
	}

	bool wentRight() {
		return  (rightIntensity() > leftIntensity());
	}

	bool wentAhead() {
	}

	bool wentNowhere() {
	}

private:
	int leftIntensity() {
		return (leftEyeLevel - baseLeftLevel) * leftRightAdjust;
	}

	int rightIntensity() {
		return rightEyeLevel - baseRightLevel;
	}

	void gaugeBase() {
		this->baseLeftLevel = api->_analogRead(leftEyePin);
		this->baseRightLevel = api->_analogRead(rightEyePin);
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
