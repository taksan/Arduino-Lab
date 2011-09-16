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
		bot->setThrustAndWait(initialThrustForStartFromFront);
		bot->setDirectionAndWait(dirToStartMovingFromFront);
	}
	else {
		bot->setThrustAndWait(initialThrustForStartFromBack);
		bot->setDirectionAndWait(dirToStartMovingFromBack);
	}
}

void StepAction::updateStepDirection()
{
	stable = false;
	if (bot->getThrustAngle() >= backThrustTurningPoint) {
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		direction=-1;
		stable = true;
	}

	if (bot->getThrustAngle() <= frontThrustTurningPoint) {
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		direction=1;
		stable = true;
	}
}

int16_t StepAction::getThrustStep()
{
	return thrustStep * direction;
}

void TurnMove::perform(int16_t intensity) {
	if (isPastTheFinalAngle(bot->getDirectionAngle())) {
		bot->setThrustAndWait(angleToReinit);
		setup();
	}
	int16_t angleStep = INTENSITY_FACTOR(intensity) * angleIncrement;
	int16_t directionAngle = bot->getDirectionAngle()+angleStep;
	bot->setDirectionAndWait(directionAngle);
}

void TurnMove::setup() {
	bot->setDirectionAndWait(directionToStartMoving);
	bot->setThrustAndWait(thrustToStartMoving);
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


void NonBlockingMove::perform(int16_t intensity) {
	if (bot->isReady()) {
		decorated->perform(intensity);
	}
}

void NonBlockingMove::setup() {
	if (bot->isReady()) {
		decorated->setup();
	}
}

void NonBlockingMove::stop()
{
	if (bot->isReady()) {
		decorated->stop();
	}
}

