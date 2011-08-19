#include "PaperBot.h"

PaperBot::PaperBot(int thrustPort, int directionPort) 
{
	thrustMotor = new Servo();
	thrustMotor->attach(thrustPort);
	setThrust(DIR_0_INIT_THRUST_ANGLE);

	directionMotor= new Servo();
	directionMotor->attach(directionPort);
	setDirection(INIT_DIR);

	facingDirection = ahead;
	lastMove= none;
	move = NULL;

	stepAheadAction = new StepAhead(this);
	stepBackAction  = new StepBack(this);

	turnRightWhenFacingBack = new TurnRightWhenFacingBack(this);;

	turnLeftWhenFacingAhead = new TurnLeftWhenFacingAhead(this);
	turnLeftWhenFacingBack = new TurnLeftWhenFacingBack(this);;

	noMove = new NoMovement();
}

void PaperBot::stepAhead(int intensity) {
	if (lastMove != movingAhead) {
		move = stepAheadAction;
		move->setup();
	}
	move->perform(intensity);
	
	lastMove = movingAhead;
	facingDirection = ahead;
}

void PaperBot::stepBack(int intensity) {
	if (lastMove != movingBack) {
		move = stepBackAction;
		move->setup();
	}

	move->perform(intensity);

	lastMove = movingBack;
	facingDirection = back;
}

void PaperBot::turnRight(int intensity) {
	if (lastMove != turningRight) {
		setupForRight();
	}
	move->perform(intensity);

	lastMove = turningRight;
}

void PaperBot::turnLeft(int intensity) {
	if (lastMove != turningLeft) {
		setupForLeft();
	}
	move->perform(intensity);

	lastMove = turningLeft;
}

void PaperBot::stop()
{
	if (lastMove == none)
		return;

	move->stop();
	move = noMove;

	lastMove = none;
}

void PaperBot::setDirection(int angle) {
	if (directionAngle == angle) 
		return;
	directionAngle = angle;
	directionMotor->write(angle);
}

void PaperBot::setThrustAndWait(int angle) {
	if (angle == thrustAngle)
		return;
	int previousAngle = thrustAngle;
	setThrust(angle);

	waitBasedOnAngleOffset(previousAngle, angle);
}

void PaperBot::setDirectionAndWait(int angle) {
	if (angle == directionAngle)
		return;
	int previousAngle = directionAngle;

	setDirection(angle);

	waitBasedOnAngleOffset(previousAngle, angle);
}

void PaperBot::setThrust(int angle) {
	if (angle == thrustAngle)
		return;
	thrustAngle = angle;
	thrustMotor->write(angle);
}

void PaperBot::ensureMotorPosition() {
	thrustMotor->write(thrustAngle);
	directionMotor->write(directionAngle);
}

int PaperBot::getDirectionAngle() {
	return directionAngle;
}

int PaperBot::getThrustAngle() {
	return thrustAngle;
}

void PaperBot::setupForRight() {
	move = turnRightWhenFacingBack;
	move->setup();
}

void PaperBot::setupForLeft() {
	if (facingDirection == ahead) {
		move = turnLeftWhenFacingAhead;
	}
	else {
		move = turnLeftWhenFacingBack;
	}
	move->setup();
}


void PaperBot::waitBasedOnAngleOffset(int previousAngle, int newAngle)
{
	int angleOffset = ABS(previousAngle - newAngle);
	long timeToWait = TIME_TO_DO_180 * (angleOffset / (float)END_DIR);
	delay(timeToWait);
}
