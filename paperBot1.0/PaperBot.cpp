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

	turnRightWhenFacingAhead = new TurnRightWhenFacingAhead(this);
	turnRightWhenFacingBack = new TurnRightWhenFacingBack(this);;

	turnLeftWhenFacingAhead = new TurnLeftWhenFacingAhead(this);
	turnLeftWhenFacingBack = new TurnLeftWhenFacingBack(this);;

	noMove = new NoMovement();
}

void PaperBot::stepAhead() {
	if (lastMove != movingAhead) {
		move = stepAheadAction;
	}
	

	if (thrustAngle == DIR_0_INIT_THRUST_ANGLE) {
		setDirectionAndWait(INIT_DIR);
		setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	}
	else {
		setDirectionAndWait(END_DIR);
		setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	}
	lastMove = movingAhead;
	facingDirection = ahead;
}

void PaperBot::stepBack() {
	if (thrustAngle == DIR_0_INIT_THRUST_ANGLE) {
		setDirectionAndWait(END_DIR);
		setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
	}
	else {
		setDirectionAndWait(INIT_DIR);
		setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
	}
	lastMove = movingBack;
	facingDirection = back;
}

void PaperBot::turnRight() {
	if (lastMove != turningRight) {
		setupForRight();
	}
	move->perform();

	lastMove = turningRight;
}

void PaperBot::turnLeft() {
	if (lastMove != turningLeft) {
		setupForLeft();
	}
	move->perform();

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
	if (facingDirection == ahead) {
		move = turnRightWhenFacingAhead;
	}
	else {
		move = turnRightWhenFacingBack;
	}
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
	long timeToWait = 500 * (angleOffset / (float)END_DIR);
	delay(timeToWait);
}
