#ifndef FOLLOW_THE_LIGHT_GAME__
#define FOLLOW_THE_LIGHT_GAME__

#include "led.h"
#include "PaperBot.h"
#include "BotGame.h"

#include "AbstractLightDirectionDetector.h"

#define SPEED 127

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
			bot->turnLeft(SPEED);
			leftLed.turnOn();
		}

		if (directionToGo == dvTurnRight) {
			bot->turnRight(SPEED);
			rightLed.turnOn();
		}

		if (directionToGo == dvGoAhead) {
			bot->stepAhead(SPEED);
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
