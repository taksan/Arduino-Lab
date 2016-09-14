#ifndef WALKING_GAME__H_
#define WALKING_GAME__H_
#include "PaperBot.h"
#include "BotGame.h"
#include "SerialDebug.h"

#define FN_PTR(object,ptrToMember)  ((object)->*(ptrToMember))
typedef void (PaperBot::*PaperBotMoveFn)(int16_t);

class WalkingGame : public BotGame {
public:
	WalkingGame(PaperBot * bot, Joy * joy)
	{
		this->bot = bot;
		this->joy = joy;
		lastMoveType = PaperBot::none;
	}

	virtual void doTick()
	{
		int16_t lastMoveIntensity = joy->getLastMoveIntensity();
		PaperBotMoveFn fn = NULL;

		PaperBot::MoveType currentMove = PaperBot::none;
		if (joy->upJoy()) {
			fn = &PaperBot::stepAhead;
			currentMove = PaperBot::movingAhead;
		}
		if (joy->downJoy()) {
			fn = &PaperBot::stepBack;
			currentMove = PaperBot::movingBack;
		}
		if (joy->rightJoy()) {
			fn = &PaperBot::turnRight;
			currentMove = PaperBot::turningRight;
		}
		if (joy->leftJoy()) {
			fn = &PaperBot::turnLeft;
			currentMove = PaperBot::turningLeft;
		}
		if (!bot->isReady() && currentMove == lastMoveType)
			return;
		lastMoveType = currentMove;

		if (fn) {
			SerialDebug::println("Will move %d", currentMove);
			FN_PTR(bot,fn)(lastMoveIntensity);
			setWaitProportionalToGivenIntensity(lastMoveIntensity);
		}
		else {
			bot->stop();
		}
	}
private:
	PaperBot * bot;
	Joy * joy;
	PaperBot::MoveType lastMoveType;
};

#endif
