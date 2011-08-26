#ifndef FOLLOW_THE_LIGHT_GAME__
#define FOLLOW_THE_LIGHT_GAME__

#include "led.h"
#include "PaperBot.h"
#include "BotGame.h"

#include "AbstractLightDirectionDetector.h"

class FollowTheLightGame : public BotGame {
public:
	FollowTheLightGame(PaperBot * bot, AbstractLightDirectionDetector * lightDirection, int16_t leftLedPin, int8_t rightLedPin):
		leftLed(leftLedPin),
		rightLed(rightLedPin)
	{
		this->bot = bot;
		this->lightDirection = lightDirection;
		previous = dvGoNowhere;
	}

	virtual void tick()
	{
		lightDirection->update();
		Direction directionToGo = lightDirection->getDirectionToGo();
		if (directionToGo != previous) {
			leftLed.turnOff();
			rightLed.turnOff();
		}
		previous = directionToGo;
		if (directionToGo == dvTurnLeft) {
			bot->turnLeft(127);
			leftLed.turnOn();
		}

		if (directionToGo == dvTurnRight) {
			bot->turnRight(127);
			rightLed.turnOn();
		}

		if (directionToGo == dvGoAhead) {
			bot->stepAhead(127);
			rightLed.turnOn();
			leftLed.turnOn();
		}
	}
private:
	PaperBot * bot;
	AbstractLightDirectionDetector * lightDirection;
	Led leftLed;
	Led rightLed;
	Direction previous;
};


#endif
