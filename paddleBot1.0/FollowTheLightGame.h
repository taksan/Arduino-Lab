#ifndef FOLLOW_THE_LIGHT_GAME__
#define FOLLOW_THE_LIGHT_GAME__

#include "led.h"
#include "PaperBot.h"
#include "BotGame.h"

#include "AbstractLightDirectionDetector.h"

#define MAX_INTENSITY 127

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
		if (!isReady())
			return;

		lightDirection->update();
		Direction directionToGo = lightDirection->getDirectionToGo();
		if (directionToGo != previous) {
			leftLed.turnOff();
			rightLed.turnOff();
		}
		previous = directionToGo;
		int acc = lightDirection->getAccuracy();
		float accuracy = lightDirection->getAccuracy()/100.0;
		int16_t intensity = MAX_INTENSITY * accuracy;
		if (intensity < 25)
			intensity = 25;
		
		if (directionToGo == dvTurnLeft) {
			bot->turnLeft(intensity);
			leftLed.turnOn();
		}

		if (directionToGo == dvTurnRight) {
			bot->turnRight(intensity);
			rightLed.turnOn();
		}

		if (directionToGo == dvGoAhead) {
			bot->stepAhead(intensity);
			rightLed.turnOn();
			leftLed.turnOn();
		}
		setWaitProportionalToGivenIntensity(intensity);
	}
private:
	PaperBot * bot;
	AbstractLightDirectionDetector * lightDirection;
	Led leftLed;
	Led rightLed;
	Direction previous;
};


#endif
