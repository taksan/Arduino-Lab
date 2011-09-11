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
		nextReadyTime = millis();
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
			SerialDebug::println("Read UP");
		}
		if (joy->downJoy()) {
			readMove = true;
			bot->stepBack(lastMoveIntensity);
			SerialDebug::println("Read DOWN");
		}
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight(lastMoveIntensity);
			SerialDebug::println("Read RIGHT");
		}
		if (joy->leftJoy()) {
			readMove = true;
			bot->turnLeft(lastMoveIntensity);
			SerialDebug::println("Read LEFT");
		}
		if (!readMove) {
			bot->stop();
		}
		else {
			int16_t timeToWait = (127-ABS(lastMoveIntensity))*2;
			nextReadyTime = millis() + timeToWait;
			SerialDebug::println("intensity: %d %d timeToWait: %d", 3, lastMoveIntensity ,  timeToWait);
		}
	}
private:
	PaperBot * bot;
	Joy * joy;
	int32_t nextReadyTime;

	bool isReady() {
		return millis() > nextReadyTime;
	}
};

#endif
