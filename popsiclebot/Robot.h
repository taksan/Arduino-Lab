#include "Controller.h"
#include "Leg.h"

class Robot {
	LeftLeg * left;
	RightLeg * right;
	Controller * controller;
public:
	Robot(Controller  * controller) {
		left = new LeftLeg(6,7,8,9);
		right = new RightLeg(10,11,12,13);

		left->knee(135);
		right->knee(135);
		this->controller = controller;
	}

	void processCommand(char * command) {
		int chosenLeg = command[0];
		char legMotor = command[1];
		char * angleStr = command+3;
		int angle = atoi(angleStr);
		Leg * legToMove;
		if (chosenLeg == 'l') {
			legToMove = (LeftLeg*)left;
			controller->print("left leg:");
		}
		else if (chosenLeg == 'r') {
			controller->print("right leg:");
			legToMove = (RightLeg*)right;
		}
		else {
			controller->print("invalid leg: ");
			controller->println(chosenLeg);
			return;
		}

		switch(legMotor) {
			case 's':
				controller->print("move shoulder motor to ");
				controller->println(angle,DEC);
				legToMove->shoulder(angle);
				break;
			case 'u':
				legToMove->upper(angle);
				controller->print("move upper motor to ");
				controller->println(angle,DEC);
				break;
			case 'k':
				legToMove->knee(angle);
				controller->print("move knee motor to ");
				controller->println(angle,DEC);
				break;

			case 'f':
				legToMove->foot(angle);
				controller->print("move foot motor to ");
				controller->println(angle,DEC);
				break;
			default:
				controller->print("invalid leg motor: ");
				controller->println(legMotor);
		}
	}
};


