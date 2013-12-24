#include "Leg.h"

class Robot {
	LeftLeg * left;
	RightLeg * right;
	FeedbackCallback * controller;
public:
	Robot(FeedbackCallback * controller):
		controller(controller)
	{
		left = new LeftLeg(controller, 6,7,8,9);
		right = new RightLeg(controller, 10,11,12,13);

		left->shoulder(90);
		left->upper(80);
		left->knee(135);
		left->foot(92);

		right->shoulder(90);
		right->upper(90);
		right->knee(135);
		right->foot(85);
		this->controller = controller;
	}

	void processCommand(char * command) {
		int chosenLeg = command[0];
		char legMotor = command[1];
		char * angleStr = command+3;
		int angle = atoi(angleStr);
		Leg * legToRotate;
		if (chosenLeg == 'l') {
			legToRotate = (LeftLeg*)left;
			controller->print("left leg:");
		}
		else if (chosenLeg == 'r') {
			controller->print("right leg:");
			legToRotate = (RightLeg*)right;
		}
		else {
			controller->print("invalid leg: ");
			controller->println(chosenLeg);
			return;
		}

		bool success;
		const char * limb;
		#define ROTATE_MOTOR(func) \
			success = legToRotate->func(angle);\
			limb = #func;\
			break;

		switch(legMotor) {
			case 's': ROTATE_MOTOR(shoulder)
			case 'u': ROTATE_MOTOR(upper)
			case 'k': ROTATE_MOTOR(knee)
			case 'f': ROTATE_MOTOR(foot)
			default:
				controller->print("invalid leg motor: ");
				controller->println(legMotor);
		}
		#undef ROTATE_MOTOR
		if (success) \
			controller->printf("rotate %s motor to %d\n", limb, angle);\

	}

};
