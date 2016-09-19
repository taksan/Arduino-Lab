#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <Arduino.h>
#include <ServoTimer2.h>
#include "Common.h"
#include "SerialDebug.h"
#include "MoveQueue.h"

#include "PaperBotMove.h"

#define Servo ServoTimer2

class PaperBot
{
public:
	PaperBot(int16_t thrustPort, int8_t directionPort); 

	void stop();

	void setDirection(int16_t angle); 

	virtual void setThrustAndWait(int16_t angle); 

	virtual void setDirectionAndWait(int16_t angle); 

	void setThrust(int16_t angle); 

	void hold(int16_t delay);

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

	void go(MoveDirection direction, int16_t intensity);

protected:
	void stepAhead(int16_t intensity);
	void stepBack(int16_t intensity);
	void turnRight(int16_t intensity);
	void turnLeft(int16_t intensity);

	MoveQueue moveQueue;
	Servo * thrustMotor;
	Servo * directionMotor;

private:
	void setupForRight(); 
	void setupForLeft(); 

	void waitBasedOnAngleOffset(int16_t previousAngle, int16_t newAngle);
	int32_t calcDelayBasedOnAngleOffset(int16_t previousAngle, int16_t newAngle);

	enum Direction {
		ahead,
		back
	};

	Direction facingDirection;
	MoveType lastMove;

	int16_t thrustAngle;
	int16_t directionAngle;

	PaperBotMove * move;

	PaperBotMove * turnRightWhenFacingBack;

	PaperBotMove * turnLeftWhenFacingAhead;
	PaperBotMove * turnLeftWhenFacingBack;
	PaperBotMove * stepAheadAction;
	PaperBotMove * stepBackAction;

	PaperBotMove * noMove;

	uint32_t commandExpirationTime;

	bool stable;

	bool cycleStarted;

	MoveDirection lastDirection;
};


#endif
