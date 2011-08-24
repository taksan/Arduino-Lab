#ifndef FOLLOW_THE_LIGHT_GAME__
#define FOLLOW_THE_LIGHT_GAME__

#include "PaperBot.h"
#include "BotGame.h"

#include "AbstractLightDirectionDetector.h"

class FollowTheLightGame : public BotGame {
public:
	FollowTheLightGame(PaperBot * bot, AbstractLightDirectionDetector * lightDirection)
	{
		this->bot = bot;
		this->lightDirection = lightDirection;
	}

	virtual void tick()
	{
		lightDirection->update();
		Direction directionToGo = lightDirection->getDirectionToGo();
		if (directionToGo == dvTurnLeft) {
			bot->turnLeft(127);
		}

		if (directionToGo == dvTurnRight) {
			bot->turnRight(127);
		}

		if (directionToGo == dvGoAhead) {
			bot->stepAhead(127);
		}
	}
private:
	PaperBot * bot;
	AbstractLightDirectionDetector * lightDirection;
};


#endif
