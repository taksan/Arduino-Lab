#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "SerialDebug.h"
#include "ArduinoApi.h"
#include "Eye.h"
#include "AbstractLightDirectionDetector.h"

class LightDirectionDetector : public AbstractLightDirectionDetector {
public:
	LightDirectionDetector(Eye *leftEye, Eye *rightEye):
		leftEye(leftEye),
		rightEye(rightEye),
		lastTakenDirection(dvTurnRight),
		accuracy(0)
	{
		this->gaugeBase();
		leftEye->setAdjustFactorAgainst(rightEye->getLevel());
	}

	void update() {
		leftEye->update();
		rightEye->update();
		lastTakenDirection = getDirectionToGo();
	}

	Direction getDirectionToGo() 
	{
		int previousAccuracy = accuracy;
		accuracy = 100;
		if (leftEye->isStronglyInfluenced() && rightEye->isStronglyInfluenced()) {
			return dvGoAhead;
		}
		if (leftEye->isStronglyInfluenced() && rightEye->isWeaklyInfluenced()) {
			return dvTurnLeft;
		}
		if (rightEye->isStronglyInfluenced() && leftEye->isWeaklyInfluenced()) {
			return dvTurnRight;
		}
		accuracy = previousAccuracy;
		return determineDirectionOnWeakLevels();
	}

	void printDebugInfo() {
		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEye->getLevel(), rightEye->getLevel());
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftEye->getIntensity(), rightEye->getIntensity());
		SerialDebug::println("Direction to go : %d", lastTakenDirection);
	}

	int getAccuracy() {
		return accuracy;
	}
private:
	Direction determineDirectionOnWeakLevels() {
		int previousAccuracy = accuracy;

		accuracy = 50;
		if (lightWentLeft()) {
			return dvTurnLeft;
		}
		if (lightWentRight()) {
			return dvTurnRight;
		}

		if (previousAccuracy <= 20)
			accuracy = 10;
		else
			accuracy -= 10;

		if (leftEye->isStrongerThan(rightEye)) {
			return dvTurnLeft;
		}

		return lastTakenDirection;
	}

	bool lightWentLeft() {
		return (leftEye->previousIntensityWasStrong());
	}

	bool lightWentRight() {
		return (rightEye->previousIntensityWasStrong());
	}


	void gaugeBase() {
		leftEye->gaugeBase();
		rightEye->gaugeBase();
	}

	Eye * leftEye;
	Eye * rightEye;
	Direction lastTakenDirection;

	int accuracy;
};

#endif
