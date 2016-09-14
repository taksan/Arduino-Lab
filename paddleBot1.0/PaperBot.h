#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <Arduino.h>
#include <ServoTimer2.h>
#include "Common.h"

#include "PaperBotMove.h"
#define TIME_TO_DO_180 200

#define Servo ServoTimer2

class PaperBot
{
public:
	PaperBot(int16_t thrustPort, int8_t directionPort); 

	void stepAhead(int16_t intensity);

	void stepBack(int16_t intensity);

	void turnRight(int16_t intensity);

	void turnLeft(int16_t intensity);

	void stop();

	void setDirection(int16_t angle); 

	void setThrustAndWait(int16_t angle); 

	void setDirectionAndWait(int16_t angle); 

	void setThrust(int16_t angle); 

	void ensureMotorPosition();

	int16_t getDirectionAngle(); 

	int16_t getThrustAngle(); 

	bool isReady();

	bool isStable();

	enum MoveType {
		none,
		movingAhead,
		movingBack,
		turningRight,
		turningLeft
	};

private:

	void setupForRight(); 

	void setupForLeft(); 

	void waitBasedOnAngleOffset(int16_t previousAngle, int16_t newAngle);

	enum Direction {
		ahead,
		back
	};

	Direction facingDirection;
	MoveType lastMove;

	int16_t thrustAngle;
	int16_t directionAngle;

	Servo * thrustMotor;
	Servo * directionMotor;
	PaperBotMove * move;

	PaperBotMove * turnRightWhenFacingBack;

	PaperBotMove * turnLeftWhenFacingAhead;
	PaperBotMove * turnLeftWhenFacingBack;
	PaperBotMove * stepAheadAction;
	PaperBotMove * stepBackAction;

	PaperBotMove * noMove;

	uint32_t commandExpirationTime;

	bool stable;
};


#endif
