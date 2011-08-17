#ifndef WALKING_GAME__H_
#define WALKING_GAME__H_
#include "PaperBot.h"
#include "BotGame.h"

class WalkingGame : public BotGame {
public:
	WalkingGame(PaperBot * bot, Joy * joy)
	{
		this->bot = bot;
		this->joy = joy;
	}

	virtual void tick()
	{
		boolean readMove = false;
		if (joy->upJoy()) {
			readMove = true;
			bot->stepAhead(127);
		}
		if (joy->downJoy()) {
			readMove = true;
			bot->stepBack(127);
		}
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight(127);
		}
		if (joy->leftJoy()) {
			readMove = true;
			bot->turnLeft(127);
		}
		if (!readMove) {
			bot->stop();
		}
	}
private:
	PaperBot * bot;
	Joy * joy;
};

#endif
