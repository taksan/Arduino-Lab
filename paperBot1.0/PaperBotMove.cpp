#include "PaperBotMove.h"
#include "PaperBot.h"

void StepAction::perform()
{
	updateStepDirection();
	bot->setThrustAndWait(bot->getThrustAngle()+getThrustStep());
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
	if (bot->getThrustAngle() <= DIR_0_INIT_THRUST_ANGLE) {
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		direction=1;
	}
	if (bot->getThrustAngle() >= DIR_180_INIT_THRUST_ANGLE) {
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		direction=-1;
	}
}

int StepAction::getThrustStep()
{
	return thrustStep * direction;
}

void TurnMove::perform() {
	if (isPastTheFinalAngle(bot->getDirectionAngle())) {
		bot->setThrustAndWait(angleToReinit);
		setup();
	}
	bot->setDirectionAndWait(bot->getDirectionAngle()+angleIncrement);
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

