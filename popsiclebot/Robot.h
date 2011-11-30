#include "Leg.h"

class Robot {
LeftLeg * left;
RightLeg * right;

public:
	Robot() {
		left = new LeftLeg(8,9,10);
		right = new RightLeg(11,12,13);

		left->upper(60);
		left->knee(45);
		right->knee(45);
	}

	void processCommand(char * command) {
		int chosenLeg = command[0];
		char legMotor = command[1];
		char * angleStr = command+3;
		int angle = atoi(angleStr);
		Leg * legToMove;
		if (chosenLeg == 'l')
			legToMove = (LeftLeg*)left;
		else
			legToMove = (RightLeg*)right;

		switch(legMotor) {
			case 'u':
				legToMove->upper(angle);
				break;
			case 'm':
				legToMove->middle(angle);
				break;
			case 'k':
				legToMove->knee(angle);
				break;
		}

	}
};


