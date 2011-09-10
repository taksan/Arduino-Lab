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
		boolean readMove = false;
		if (joy->upJoy()) {
			readMove = true;
			bot->stepAhead(127);
			SerialDebug::println("Read UP");
		}
		if (joy->downJoy()) {
			readMove = true;
			bot->stepBack(127);
			SerialDebug::println("Read DOWN");
		}
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight(127);
			SerialDebug::println("Read RIGHT");
		}
		if (joy->leftJoy()) {
			readMove = true;
			bot->turnLeft(127);
			SerialDebug::println("Read LEFT");
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
