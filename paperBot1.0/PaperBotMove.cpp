#include "PaperBotMove.h"
#include "PaperBot.h"

void StepAhead::perform()
{
	if (bot->getThrustAngle() == DIR_0_INIT_THRUST_ANGLE) {
		bot->setDirectionAndWait(INIT_DIR);
		bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	}
	else {
		bot->setDirectionAndWait(END_DIR);
		bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	}
}

void StepAhead::setup()
{
}

void StepAhead::stop()
{
}

void StepBack::perform()
{
	if (bot->getThrustAngle() == DIR_0_INIT_THRUST_ANGLE) {
		bot->setDirectionAndWait(END_DIR);
		bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	}
	else {
		bot->setDirectionAndWait(INIT_DIR);
		bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	}
}

void StepBack::setup()
{
}

void StepBack::stop()
{
}



void TurnMove::perform() {
	if (isTheEndAngle(bot->getDirectionAngle())) {
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

