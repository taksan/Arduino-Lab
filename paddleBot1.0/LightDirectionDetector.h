#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "SerialDebug.h"
#include "ArduinoApi.h"
#include "Eye.h"
#include "AbstractLightDirectionDetector.h"

#define STUBBORN_AHEAD_TIMES 3

class LightDirectionDetector : public AbstractLightDirectionDetector {
public:
	LightDirectionDetector(Eye *leftEye, Eye *rightEye):
		leftEye(leftEye),
		rightEye(rightEye),
		lastTakenDirection(dvTurnRight),
		accuracy(0),
		aheadStubbornCount(0)
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
		bool hasStrong = false;
		int previousAccuracy = accuracy;
		accuracy = 100;
		if (leftEye->isStronglyInfluenced() && rightEye->isStronglyInfluenced()) {
			aheadStubbornCount = 0;
			return dvGoAhead;
		}

		if (leftEye->isStronglyInfluenced() && rightEye->isWeaklyInfluenced()) {
			lastStrongMove = dvTurnLeft;
			hasStrong = true;
		}

		if (rightEye->isStronglyInfluenced() && leftEye->isWeaklyInfluenced()) {
			lastStrongMove = dvTurnRight;
			hasStrong = true;
		}

		if (isPreferToGoAhead()) {
			accuracy = 80;
			return dvGoAhead;
		}

		if (lastTakenDirection == dvGoAhead) {
			return lastStrongMove;
		}

		if (hasStrong) {
			return lastStrongMove;
		}


		accuracy = previousAccuracy;
		return determineDirectionOnWeakLevels();
	}

	void printDebugInfo() {
		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEye->getLevel(), rightEye->getLevel());
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftEye->getIntensity(), rightEye->getIntensity());
		SerialDebug::println("Direction to go : %d", lastTakenDirection);
	}

	int getIntensity() {
		return accuracy;
	}
private:
	Direction determineDirectionOnWeakLevels() {
		int previousAccuracy = accuracy;

		accuracy = 80;
		if (lightWentLeft()) {
			return dvTurnLeft;
		}
		if (lightWentRight()) {
			return dvTurnRight;
		}

		if (previousAccuracy <= 25)
			accuracy = 20;
		else
			accuracy -= 5;

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

	bool isPreferToGoAhead() {
		if (lastTakenDirection != dvGoAhead) {
			aheadStubbornCount = 0;
			return false;
		}

		if (aheadStubbornCount > STUBBORN_AHEAD_TIMES)
			return false;

		aheadStubbornCount++;
		return true;
	}

	Eye * leftEye;
	Eye * rightEye;
	Direction lastTakenDirection;
	Direction lastStrongMove;

	int accuracy;
	int8_t aheadStubbornCount;
};

#endif
