#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "SerialDebug.h"
#include "ArduinoApi.h"
#include "Eye.h"

class LightDirectionDetector {
public:
	enum Direction {
		goAhead,
		turnLeft,
		turnRight
	};

	LightDirectionDetector(Eye *leftEye, Eye *rightEye):
		leftEye(leftEye),
		rightEye(rightEye),
		lastTakenDirection(turnRight)
	{
		this->gaugeBase();
		leftEye->setAdjustFactorAgainst(rightEye->getLevel());

	}

	void update() {
		leftEye->update();
		rightEye->update();

		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEye->getLevel(), rightEye->getLevel());
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftEye->getIntensity(), rightEye->getIntensity());
	}

	Direction getDirectionToGo() {
		if (leftEye->isStronglyInfluenced() && rightEye->isStronglyInfluenced()) {
			return goAhead;
		}
		if (leftEye->isStronglyInfluenced() && rightEye->isWeaklyInfluenced()) {
			return turnLeft;
		}
		if (rightEye->isStronglyInfluenced() && leftEye->isWeaklyInfluenced()) {
			return turnRight;
		}

		return determineDirectionOnWeakLevels();
	}

private:
	Direction determineDirectionOnWeakLevels() {
		if (lightWentLeft()) {
			return turnLeft;
		}
		if (lightWentRight()) {
			return turnRight;
		}
		if (leftEye->isStrongerThan(rightEye)) {
			return turnLeft;
		}

		return turnRight;
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
