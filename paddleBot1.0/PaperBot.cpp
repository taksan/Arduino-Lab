#include "PaperBot.h"
#include "SerialDebug.h"

PaperBot::PaperBot(int16_t thrustPort, int8_t directionPort) 
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
	turnRightWhenFacingBack = new TurnRightWhenFacingBack(this);
	turnLeftWhenFacingAhead = new TurnLeftWhenFacingAhead(this);
	turnLeftWhenFacingBack = new TurnLeftWhenFacingBack(this);
	noMove = new NoMovement();
	
	commandExpirationTime = millis();
}

void PaperBot::stepAhead(int16_t intensity) {
	if (lastMove != movingAhead) {
		move = stepAheadAction;
		move->setup();
	}
	move->perform(intensity);
	
	lastMove = movingAhead;
	facingDirection = ahead;
}

void PaperBot::stepBack(int16_t intensity) {
	if (lastMove != movingBack) {
		move = stepBackAction;
		move->setup();
	}

	move->perform(intensity);

	lastMove = movingBack;
	facingDirection = back;
}

void PaperBot::turnRight(int16_t intensity) {
	if (lastMove != turningRight) {
		setupForRight();
	}
	move->perform(intensity);

	lastMove = turningRight;
}

void PaperBot::turnLeft(int16_t intensity) {
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

void PaperBot::setDirection(int16_t angle) {
	if (directionAngle == angle) 
		return;
	directionAngle = angle;
	directionMotor->write(angle);
}

void PaperBot::setThrustAndWait(int16_t angle) {
	if (angle == thrustAngle)
		return;
	int previousAngle = thrustAngle;
	setThrust(angle);

	waitBasedOnAngleOffset(previousAngle, angle);
}

void PaperBot::setDirectionAndWait(int16_t angle) {
	if (angle == directionAngle)
		return;
	int previousAngle = directionAngle;

	setDirection(angle);

	waitBasedOnAngleOffset(previousAngle, angle);
}

void PaperBot::setThrust(int16_t angle) {
	if (angle == thrustAngle)
		return;
	thrustAngle = angle;
	thrustMotor->write(angle);
}

void PaperBot::ensureMotorPosition() {
	thrustMotor->write(thrustAngle);
	directionMotor->write(directionAngle);
}

int16_t PaperBot::getDirectionAngle() {
	return directionAngle;
}

int16_t PaperBot::getThrustAngle() {
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


void PaperBot::waitBasedOnAngleOffset(int16_t previousAngle, int16_t newAngle)
{
	int16_t angleOffset = ABS(previousAngle - newAngle);
	int32_t timeToWait = TIME_TO_DO_180 * (angleOffset / (float)END_DIR);

	commandExpirationTime = millis() + timeToWait;
	delay(timeToWait);
}

bool PaperBot::isReady()
{
	return millis() > commandExpirationTime; 
}

bool PaperBot::isStable() {
	return move->isStable();
}
