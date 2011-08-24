#include "PaperBotMove.h"
#include "PaperBot.h"

void StepAction::perform(int intensity)
{
	updateStepDirection();
	int thrustStep = getThrustStep() * INTENSITY_FACTOR(intensity);
	int thrustAngle = bot->getThrustAngle()+thrustStep;
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
	if (bot->getThrustAngle() <= frontThrustTurningPoint) {
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		direction=1;
	}
	if (bot->getThrustAngle() >= backThrustTurningPoint) {
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		direction=-1;
		bot->setThrust(170);
	}
}

int StepAction::getThrustStep()
{
	return thrustStep * direction;
}

void TurnMove::perform(int intensity) {
	if (isPastTheFinalAngle(bot->getDirectionAngle())) {
		bot->setThrustAndWait(angleToReinit);
		setup();
	}
	int angleStep = INTENSITY_FACTOR(intensity) * angleIncrement;
	int directionAngle = bot->getDirectionAngle()+angleStep;
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


void NonBlockingMove::perform(int intensity) {
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

