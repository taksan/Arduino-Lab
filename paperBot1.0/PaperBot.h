#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <WProgram.h>
#include <ServoTimer2.h>
#include "Common.h"

#include "PaperBotMove.h"
#define TIME_TO_DO_180 250

#define Servo ServoTimer2

class PaperBot
{
public:
	PaperBot(int thrustPort, int directionPort); 

	void stepAhead(int intensity);

	void stepBack(int intensity);

	void turnRight(int intensity);

	void turnLeft(int intensity);

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

	TurnRightWhenFacingBack * turnRightWhenFacingBack;

	TurnLeftWhenFacingAhead * turnLeftWhenFacingAhead;
	TurnLeftWhenFacingBack * turnLeftWhenFacingBack;
	StepAhead * stepAheadAction;
	StepBack  * stepBackAction;

	NoMovement * noMove;
};

#endif
