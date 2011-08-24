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
		lastTakenDirection(dvTurnRight)
	{
		this->gaugeBase();
		leftEye->setAdjustFactorAgainst(rightEye->getLevel());

	}

	void update() {
		leftEye->update();
		rightEye->update();
		lastTakenDirection = getDirectionToGo();

		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEye->getLevel(), rightEye->getLevel());
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftEye->getIntensity(), rightEye->getIntensity());
	}

	Direction getDirectionToGo() 
	{
		if (leftEye->isStronglyInfluenced() && rightEye->isStronglyInfluenced()) {
			return dvGoAhead;
		}
		if (leftEye->isStronglyInfluenced() && rightEye->isWeaklyInfluenced()) {
			return dvTurnLeft;
		}
		if (rightEye->isStronglyInfluenced() && leftEye->isWeaklyInfluenced()) {
			return dvTurnRight;
		}

		return determineDirectionOnWeakLevels();
	}

private:
	Direction determineDirectionOnWeakLevels() {
		if (lightWentLeft()) {
			return dvTurnLeft;
		}
		if (lightWentRight()) {
			return dvTurnRight;
		}
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
};

#endif
