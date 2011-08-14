#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <WProgram.h>
#include <Servo.h>
#include "Common.h"

#include "PaperBotMove.h"

class PaperBot
{
public:
	PaperBot(int thrustPort, int directionPort); 

	void stepAhead();

	void stepBack();

	void turnRight();

	void turnLeft();

	void stop();

	void setDirection(int angle); 

	void setThrustAndWait(int angle); 

	void setDirectionAndWait(int angle); 

	void setThrust(int angle); 

	void ensureMotorPosition();

	int getDirectionAngle(); 

	int getThrustAngle(); 
private:

	void setupForRight(); 

	void setupForLeft(); 

	void waitBasedOnAngleOffset(int previousAngle, int newAngle);

	enum Direction {
		ahead,
		back
	};

	enum MoveType {
		none,
		movingAhead,
		movingBack,
		turningRight,
		turningLeft
	};


	Direction facingDirection;
	MoveType lastMove;

	int thrustAngle;
	int directionAngle;

	Servo * thrustMotor;
	Servo * directionMotor;
	PaperBotMove * move;

	TurnRightWhenFacingAhead * turnRightWhenFacingAhead;
	TurnRightWhenFacingBack * turnRightWhenFacingBack;

	TurnLeftWhenFacingAhead * turnLeftWhenFacingAhead;
	TurnLeftWhenFacingBack * turnLeftWhenFacingBack;
	StepAhead * stepAheadAction;
	StepBack  * stepBackAction;

	NoMovement * noMove;
};

#endif
