#ifndef PAPER_BOT_H__
#define PAPER_BOT_H__

class PaperBot
{
public:
	PaperBot(int thrustPort, int directionPort) {
		thrustAngle = 30;
		thrustMotor = new Servo();
		thrustMotor->attach(thrustPort);
		thrustMotor->write(thrustAngle);

		directionAngle = 0;
		directionMotor= new Servo();
		directionMotor->attach(directionPort);
		directionMotor->write(directionAngle);

	}

	enum moveType {
		rotateThrustMotor=1,
		rotateDirectionMotor=2
	};

	void tick() {
		
	}

	void stepAhead() {
		if (thrustAngle == 0) {
			if (directionAngle == 180)
				rotateMotorToFront();
			thrustAngle = 180;
		}
		else {
			if (directionAngle == 0)
				rotateMotorToFront();

			thrustAngle = 0;
		}
		thrustMotor->write(thrustAngle);
		delay(500);
	}

	void stepBack() {
		if (thrustAngle == 0) {
			if (directionAngle == 0)
				rotateMotorToFront();
			thrustAngle = 0;
		}
		else {
			if (directionAngle == 180)
				rotateMotorToFront();

			thrustAngle = 180;
		}
		thrustMotor->write(thrustAngle);
		delay(500);

	}

	void setDirection(int angle) {
		directionMotor->write(angle);
	}

	void setThrust(int angle) {
		thrustMotor->write(angle);
	}

private:
	void rotateMotorToFront() {
		if (directionAngle == 0) {
			directionAngle = 180;
		}
		else {
			directionAngle = 0;
		}
		directionMotor->write(directionAngle);
		delay(500);
	}

	int thrustAngle;
	int directionAngle;

	Servo * thrustMotor;
	Servo * directionMotor;

	class PaperBotCommand {
	};


};

#endif
