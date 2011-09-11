#ifndef WALKING_GAME__H_
#define WALKING_GAME__H_
#include "PaperBot.h"
#include "BotGame.h"
#include "SerialDebug.h"

class WalkingGame : public BotGame {
public:
	WalkingGame(PaperBot * bot, Joy * joy)
	{
		this->bot = bot;
		this->joy = joy;
	}

	virtual void tick()
	{
		if (!isReady()) {
			return;
		}

		boolean readMove = false;
		int16_t lastMoveIntensity = joy->getLastMoveIntensity();
		if (joy->upJoy()) {
			readMove = true;
			bot->stepAhead(lastMoveIntensity);
		}
		if (joy->downJoy()) {
			readMove = true;
			bot->stepBack(lastMoveIntensity);
		}
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight(lastMoveIntensity);
		}
		if (joy->leftJoy()) {
			readMove = true;
			bot->turnLeft(lastMoveIntensity);
		}
		if (!readMove) {
			bot->stop();
		}
		else {
			int16_t timeToWait = (127-ABS(lastMoveIntensity))*2;
			if (timeToWait < 20) {
				timeToWait = 20;
			}
			setTimeToWaitUntilNextReady(timeToWait);
		}
	}
private:
	PaperBot * bot;
	Joy * joy;

};

#endif
