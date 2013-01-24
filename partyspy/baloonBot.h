#include <Servo.h>
#include "motor.h"

#define LEFT_ANGLE_MOTOR_FACING_FRONT  90
#define RIGHT_ANGLE_MOTOR_FACING_FRONT 30

#define LEFT_ANGLE_MOTOR_FACING_DOWN   20
#define RIGHT_ANGLE_MOTOR_FACING_DOWN 140

class BaloonBot {
private:
	Servo left, right;
	Motor rightHelix, leftHelix;
	enum MovePlane {
		msHoriz = 0,
		msVert
	} movePlane;

public:
	BaloonBot(int leftServo, int rightServo, int leftHelix0, int leftHelix1, int rightHelix0, int rightHelix1):
		leftHelix(leftHelix0, leftHelix1),
		rightHelix(rightHelix0, rightHelix1)
	{
		left.attach(leftServo);
		right.attach(rightServo);

		prepareHorizontalMovement();
	}

	void moveForward() {
		prepareHorizontalMovement();
		leftHelix.clockwise();
		rightHelix.clockwise();
		stop();
	}

	void moveBackward() {
		prepareHorizontalMovement();
		leftHelix.counterclockwise();
		rightHelix.counterclockwise();
		stop();
	}


	void rotateLeft() {
		prepareHorizontalMovement();
		leftHelix.clockwise();
		rightHelix.counterclockwise();
		stop();
	}

	void rotateRight() {
		prepareHorizontalMovement();
		leftHelix.counterclockwise();
		rightHelix.clockwise();
		stop();
	}

	void moveUp() {
		prepareVerticalMovement();
		leftHelix.counterclockwise();
		rightHelix.counterclockwise();
		stop();
	}

	void moveDown() {
		prepareVerticalMovement();
		leftHelix.clockwise();
		rightHelix.clockwise();
		stop();
	}

private:
	void stop() {
		delay(100);
		leftHelix.stop();
		rightHelix.stop();
	}

	void prepareHorizontalMovement() {
		if (movePlane == msHoriz)
			return;
		movePlane = msHoriz;
		left.write(LEFT_ANGLE_MOTOR_FACING_FRONT);
		right.write(RIGHT_ANGLE_MOTOR_FACING_FRONT);
		delay(100);
	}

	void prepareVerticalMovement() {
		if (movePlane == msVert)
			return;
		movePlane = msVert;
		left.write(LEFT_ANGLE_MOTOR_FACING_DOWN);
		right.write(RIGHT_ANGLE_MOTOR_FACING_DOWN);
		delay(100);
	}
};
