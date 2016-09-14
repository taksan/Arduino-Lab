#ifndef LIGHT_FOLLOW__H_
#define LIGHT_FOLLOW__H_

#include "SerialDebug.h"
#include "ArduinoApi.h"
#include "Eye.h"
#include "AbstractLightDirectionDetector.h"
#include "AbstractLightFollower.h"

#define STUBBORN_AHEAD_TIMES 3

class LightDirectionDetector : public AbstractLightDirectionDetector {
public:
	LightDirectionDetector(AbstractLightFollower * lightFollower, Eye *leftEye, Eye *rightEye):
		leftEye(leftEye),
		rightEye(rightEye),
		lastTakenDirection(dvTurnRight),
		lastKnownDirection(dvGoNowhere),
		follower(lightFollower),
		intensity(0),
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
		Direction newKnownDirection;
		intensity = 100;
		if (areBothEyesStrong()) {
			aheadStubbornCount = 0;
			return dvGoAhead;
		}

		if (isLeftStrongAndRightWeak()) {
			adjustIntensityToDetailedMovement();
			newKnownDirection = dvTurnLeft;
			hasStrong = true;
		}

		if (isRightStrongAndLeftWeak()) {
			adjustIntensityToDetailedMovement();
			newKnownDirection = dvTurnRight;
			hasStrong = true;
		}

		if (isPreferToGoAhead()) {
			intensity = 80;
			lastKnownDirection = newKnownDirection;
			return dvGoAhead;
		}

		if (follower->canChangeDirection()) {

			if (hasStrong) {
				lastKnownDirection = newKnownDirection;
				return lastKnownDirection;
			}
			return determineDirectionOnWeakLevels();
		}
		return lastTakenDirection;
	}

	void printDebugInfo() {
		SerialDebug::println("Raw: leftEye: %d rightEye: %d", leftEye->getLevel(), rightEye->getLevel());
		SerialDebug::println("Intensity: leftEye: %d rightEye: %d", leftEye->getIntensity(), rightEye->getIntensity());
		SerialDebug::println("Direction to go : %d", lastTakenDirection);
	}

	int getIntensity() {
		return intensity;
	}
private:
	Direction determineDirectionOnWeakLevels() {
		intensity = 40;
		if (lastKnownDirection != dvGoNowhere)
			return lastKnownDirection;
		
		if (leftEye->isStrongerThan(rightEye)) {
			return dvTurnLeft;
		}

		return lastTakenDirection;
	}

	bool isLeftStrongAndRightWeak() {
		return leftEye->isStronglyInfluenced() && rightEye->isWeaklyInfluenced();
	}

	bool isRightStrongAndLeftWeak() {
		return rightEye->isStronglyInfluenced() && leftEye->isWeaklyInfluenced();
	}

	bool areBothEyesStrong() {
		return leftEye->isStronglyInfluenced() && rightEye->isStronglyInfluenced();
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

	void adjustIntensityToDetailedMovement() {
		intensity = 20;
	}

	Eye * leftEye;
	Eye * rightEye;
	Direction lastTakenDirection;
	Direction lastKnownDirection;
	AbstractLightFollower * follower;

	int intensity;
	int8_t aheadStubbornCount;
};

#endif
