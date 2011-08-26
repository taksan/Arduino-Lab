#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <WProgram.h>
#include <ServoTimer2.h>
#include "Common.h"

#include "PaperBotMove.h"
#define TIME_TO_DO_180 500

#define Servo ServoTimer2

class PaperBot
{
public:
	PaperBot(int16_t thrustPort, int8_t directionPort); 

	void stepAhead(int intensity);

	void stepBack(int intensity);

	void turnRight(int intensity);

	void turnLeft(int intensity);

	void stop();

	void setDirection(int16_t angle); 

	void setThrustAndWait(int16_t angle); 

	void setDirectionAndWait(int16_t angle); 

	void setThrust(int16_t angle); 

	void ensureMotorPosition();

	int getDirectionAngle(); 

	int getThrustAngle(); 

	bool isReady();
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

	int32_t commandExpirationTime;
};

#endif
