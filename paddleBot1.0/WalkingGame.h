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

	virtual void doTick()
	{
		int16_t lastMoveIntensity = joy->getLastMoveIntensity();

		if (joy->upJoy()) {
			bot->go(mdAhead, lastMoveIntensity);
		}
		else
		if (joy->downJoy()) {
			bot->go(mdBack, lastMoveIntensity);
		}
		else
		if (joy->rightJoy()) {
			bot->go(mdRight, lastMoveIntensity);
		}
		else
		if (joy->leftJoy()) {
			bot->go(mdLeft, lastMoveIntensity);
		}
		else
			bot->stop();
	}
private:
	PaperBot * bot;
	Joy * joy;
	
};

#endif
