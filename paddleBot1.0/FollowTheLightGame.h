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
		rightLed(rightLedPin),
		bot(bot),
		lightDirection(lightDirection),
		previous(dvGoNowhere),
		goAheadUntilTurningStablePoint(false)
	{
	}

	virtual void doTick()
	{
		if (goAheadUntilTurningStablePoint) {
			if (!bot->isStable()) {
				bot->stepAhead(MAX_INTENSITY);
				setWaitProportionalToGivenIntensity(MAX_INTENSITY);
				return;
			}
		}

		lightDirection->update();
		Direction directionToGo = lightDirection->getDirectionToGo();
		if (directionToGo != previous) {
			leftLed.turnOff();
			rightLed.turnOff();
		}
		previous = directionToGo;
		int acc = lightDirection->getIntensity();
		float accuracy = lightDirection->getIntensity()/100.0;
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
	bool goAheadUntilTurningStablePoint;
};


#endif
