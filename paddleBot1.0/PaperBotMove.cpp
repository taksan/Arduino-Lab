#include "PaperBotMove.h"
#include "PaperBot.h"
#include "SerialDebug.h"

void StepAction::perform(int16_t intensity)
{
	updateStepDirection();
	int16_t thrustStep = getThrustStep() * INTENSITY_FACTOR(intensity);
	int16_t thrustAngle = bot->getThrustAngle()+thrustStep;
	bot->setThrustAndWait(thrustAngle);
}

void StepAction::setup()
{
	if (bot->getThrustAngle() < 90) {
		bot->setThrustAndWait(frontThrustTurningPoint);
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		bot->setThrustAndWait(initialThrustForStartFromFront);
	}
	else {
		bot->setThrustAndWait(backThrustTurningPoint);
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		bot->setThrustAndWait(initialThrustForStartFromBack);
	}
}

void StepAction::updateStepDirection()
{
	stable = false;
	if (bot->getThrustAngle() >= backThrustTurningPoint) {
		bot->hold(holdBetweenReverse);
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		direction=-1;
		stable = true;
	}

	if (bot->getThrustAngle() <= frontThrustTurningPoint) {
		bot->hold(holdBetweenReverse);
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		direction=1;
		stable = true;
	}
}

int16_t StepAction::getThrustStep()
{
	return thrustStep * direction;
}

void TurnMove::setup() {
	bot->setDirectionAndWait(directionToStartMoving);
	bot->setThrustAndWait(thrustToStartMoving);
}

void TurnMove::perform(int16_t intensity) {
	if (isPastTheFinalAngle(bot->getDirectionAngle())) {
		bot->setThrustAndWait(angleToReinit);
		setup();
		return;
	}
	int16_t angleStep = INTENSITY_FACTOR(intensity) * angleIncrement;
	int16_t directionAngle = bot->getDirectionAngle()+angleStep;
	bot->setDirectionAndWait(directionAngle);
}

void TurnRightWhenFacingAhead::stop() {
	bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	bot->setDirectionAndWait(END_DIR);
}

void TurnRightWhenFacingBack::stop() {
	bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	bot->setDirectionAndWait(END_DIR);
}


void TurnLeftWhenFacingAhead::stop() {
	bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	bot->setDirectionAndWait(0);
}

void TurnLeftWhenFacingBack::stop() {
	bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	bot->setDirectionAndWait(INIT_DIR);
}
