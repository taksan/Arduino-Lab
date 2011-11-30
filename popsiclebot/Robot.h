#include "Controller.h"
#include "Leg.h"

class Robot {
	LeftLeg * left;
	RightLeg * right;
	Controller * controller;
public:
	Robot(Controller  * controller) {
		left = new LeftLeg(8,9,10);
		right = new RightLeg(11,12,13);

		left->upper(60);
		left->knee(45);
		right->knee(45);
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
			case 'u':
				controller->print("move upper motor to ");
				controller->println(angle,DEC);
				legToMove->upper(angle);
				break;
			case 'm':
				legToMove->middle(angle);
				controller->print("move middle motor to ");
				controller->println(angle,DEC);
				break;
			case 'k':
				legToMove->knee(angle);
				controller->print("move knee motor to ");
				controller->println(angle,DEC);
				break;
			default:
				controller->print("invalid leg motor: ");
				controller->println(legMotor);
		}
	}
};


