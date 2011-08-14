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
			bot->stepAhead();
		}
		if (joy->downJoy()) {
			readMove = true;
			bot->stepBack();
		}
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight();
		}
		if (joy->leftJoy()) {
			readMove = true;
			bot->turnLeft();
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
