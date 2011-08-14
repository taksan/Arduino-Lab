#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__
#include <WProgram.h>

#define ABS(X) (X)<0?-(X):X

#define DIR_0_INIT_THRUST_ANGLE 10
#define DIR_180_INIT_THRUST_ANGLE 170
#define INIT_DIR 0
#define END_DIR  180

class PaperBot
{
private:
public:
	PaperBot(int thrustPort, int directionPort) {
		thrustMotor = new Servo();
		thrustMotor->attach(thrustPort);
		setThrust(DIR_0_INIT_THRUST_ANGLE);

		directionMotor= new Servo();
		directionMotor->attach(directionPort);
		setDirection(INIT_DIR);

		facingDirection = ahead;
		lastMove= none;
		move = NULL;

		turnRightWhenFacingAhead = new TurnRightWhenFacingAhead(this);
		turnRightWhenFacingBack = new TurnRightWhenFacingBack(this);;

		turnLeftWhenFacingAhead = new TurnLeftWhenFacingAhead(this);
		turnLeftWhenFacingBack = new TurnLeftWhenFacingBack(this);;

		noMove = new NoMovement();
	}

	void stepAhead() {
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

	void stepBack() {
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

	void turnRight() {
		if (lastMove != turningRight) {
			setupForRight();
		}
		move->perform();
		
		lastMove = turningRight;
	}

	void turnLeft() {
		if (lastMove != turningLeft) {
			setupForLeft();
		}
		move->perform();
		
		lastMove = turningLeft;
	}

	void stop()
	{
		if (lastMove == none)
			return;

		move->stop();
		move = noMove;

		lastMove = none;
	}

	void setDirection(int angle) {
		directionAngle = angle;
		directionMotor->write(angle);
	}

	void setThrustAndWait(int angle) {
		if (angle == thrustAngle)
			return;
		int previousAngle = thrustAngle;
		setThrust(angle);

		waitBasedOnAngleOffset(previousAngle, angle);
	}

	void setDirectionAndWait(int angle) {
		if (angle == directionAngle)
			return;
		int previousAngle = directionAngle;

		setDirection(angle);

		waitBasedOnAngleOffset(previousAngle, angle);
	}

	void setThrust(int angle) {
		if (angle == thrustAngle)
			return;
		thrustAngle = angle;
		thrustMotor->write(angle);
	}

	void ensureMotorPosition() {
		thrustMotor->write(thrustAngle);
		directionMotor->write(directionAngle);
	}

	int getDirectionAngle() {
		return directionAngle;
	}
private:

	void setupForRight() {
		if (facingDirection == ahead) {
			move = turnRightWhenFacingAhead;
		}
		else {
			move = turnRightWhenFacingBack;
		}
		move->setup();
	}

	void setupForLeft() {
		if (facingDirection == ahead) {
			move = turnLeftWhenFacingAhead;
		}
		else {
			move = turnLeftWhenFacingBack;
		}
		move->setup();
	}


	void waitBasedOnAngleOffset(int previousAngle, int newAngle)
	{
		int angleOffset = ABS(previousAngle - newAngle);
		long timeToWait = 500 * (angleOffset / (float)END_DIR);
		delay(timeToWait);
	}

	class PaperBotMove {
	public:
		virtual void perform()=0;
		virtual void setup()=0;
		virtual void stop();
	};

	class NoMovement: public PaperBotMove {
	public:
		void perform() {}

		void setup() {}
		
		void stop() {}
	};

	class TurnMove: public PaperBotMove {
	public:
		TurnMove(PaperBot * bot, int angleToReinit, int directionToStartMoving, int thrustToStartMoving, int angleIncrement) {
			this->bot = bot;
			this->angleToReinit          = angleToReinit;
			this->directionToStartMoving = directionToStartMoving;
			this->thrustToStartMoving    = thrustToStartMoving;
			this->angleIncrement         = angleIncrement;
		}

		virtual void perform() {
			if (isTheEndAngle(bot->getDirectionAngle())) {
				bot->setThrustAndWait(angleToReinit);
				setup();
			}
			bot->setDirectionAndWait(bot->getDirectionAngle()+angleIncrement);
		}
		virtual void setup() {
			bot->setDirectionAndWait(directionToStartMoving);
			bot->setThrustAndWait(thrustToStartMoving);
		}

	protected:
		virtual boolean isTheEndAngle(int angle) {
			return false;
		}
	protected:	
		PaperBot *bot;
	private:	
		int angleToReinit;
		int	directionToStartMoving;
		int	thrustToStartMoving;
		int angleIncrement;
	};

	class TurnRightWhenFacingAhead : public TurnMove {
	public:
		TurnRightWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, END_DIR, 110, -5) { }

		void stop() {
			bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
			bot->setDirectionAndWait(END_DIR);
		}
	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
	};

	class TurnRightWhenFacingBack : public TurnMove {
	public:
		TurnRightWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, END_DIR, 70, -5) { }
		void stop() {
			bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
			bot->setDirectionAndWait(END_DIR);
		}

	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
	};

	class TurnLeftWhenFacingAhead : public TurnMove {
	public:
		TurnLeftWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, INIT_DIR, 70, 5) { }

		void stop() {
			bot->setThrustAndWait(DIR_0_INIT_THRUST_ANGLE);
			bot->setDirectionAndWait(0);
		}

	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle >= END_DIR;
		}
	};

	class TurnLeftWhenFacingBack : public TurnMove {
	public:
		TurnLeftWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, INIT_DIR, 110, 5) { }
		
		void stop() {
			bot->setThrustAndWait(DIR_180_INIT_THRUST_ANGLE);
			bot->setDirectionAndWait(INIT_DIR);
		}


	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle >= END_DIR;
		}
	};


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

	NoMovement * noMove;

};

#endif
