#include "PaperBotMove.h"
#include "PaperBot.h"

void StepAction::perform()
{
	if (bot->getThrustAngle() == DIR_0_INIT_THRUST_ANGLE) {
		bot->setDirectionAndWait(dirToStartMovingFromFront);
		bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	}
	else {
		bot->setDirectionAndWait(dirToStartMovingFromBack);
		bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	}
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

