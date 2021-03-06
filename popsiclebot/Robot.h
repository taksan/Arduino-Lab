#include "feedback.h"
#include "Leg.h"

class Robot : public Tickable {
	LeftLeg * left;
	RightLeg * right;
	FeedbackCallback * controller;
	ArticulatedJoint * neck;
public:
	Robot(FeedbackCallback * controller):
		controller(controller)
	{
		left  = new LeftLeg (controller,  6, 7, 8,9);
		right = new RightLeg(controller, 13,12,11,10);
		neck = new ArticulatedJoint(controller, 0, 180);
		neck->attach(5);

		neck->write(90);
		left->init(90,60,125,120);
		right->init(90,60,55,120);
		this->controller = controller;
	}

	void tick() {
		left->tick();
		right->tick();
		neck->tick();
	}

	void processCommand(const char * command) {
		if (command[0] == 's') {
			sendRobotJson();
			return;
		}
		if (command[0] == 'n') {
			rotateNeck(command);
			return;
		}
		rotateLegJoint(command);
	}
	inline void rotateNeck(const char * command) {
		const char * angleStr = command+1;
		int angle = atoi(angleStr);
		neck->rotate(angle);
	}

	inline void rotateLegJoint(const char* command) 
	{
		char legMotor = command[1];
		const char * angleStr = command+3;
		int angle = atoi(angleStr);
		Leg * legToRotate;
		char chosenLeg = command[0];
		if (chosenLeg == 'l') {
			legToRotate = (LeftLeg*)left;
			controller->print("left ");
		}
		else if (chosenLeg == 'r') {
			legToRotate = (RightLeg*)right;
			controller->print("right ");
		}
		else {
			controller->printf("invalid leg: %c\n", chosenLeg);
			return;
		}

		bool success;
		const char * limb;
		#define TURN_JOINT(func) \
			controller->print(" " #func ":");\
			success = legToRotate->func(angle);\
			limb = #func;\
			break;

		switch(legMotor) {
			case 's': TURN_JOINT(shoulder)
			case 'u': TURN_JOINT(upper)
			case 'k': TURN_JOINT(knee)
			case 'f': TURN_JOINT(foot)
			default:
				controller->printf("invalid leg motor: %c\n", legMotor);
		}
		#undef TURN_JOINT
		if (success) \
			controller->printf("rotate %s motor to %d\n", limb, angle);\

	}

	void sendRobotJson() {
		#define FMT "{s:%d,u:%d,k:%d,f:%d}" 
		#define VALUES_OF(member) member->shoulder(), member->upper(), member->knee(), member->foot()
		controller->printf(
			"{left:" FMT ",right:" FMT ",neck:%d}\n",
			VALUES_OF(left), VALUES_OF(right),neck->read()
			);
		#undef VALUES_OF
		#undef FMT
	}
};
