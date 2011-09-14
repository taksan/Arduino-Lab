#include "BotGame.h"

class WalkingGame : public BotGame {
public:
	WalkingAction(PaperBot * bot, Joy * joy)
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
		if (joy->rightJoy()) {
			readMove = true;
			bot->turnRight();
		}
		if (!readMove) {
			bot->stop();
		}
	}
private:
	PaperBot * bot;
	Joy * joy;
};
