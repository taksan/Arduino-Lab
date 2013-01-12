#include "baloonBot.h"
#include "../serialReader/SerialReader.h"

#define LEFT_SERVO    7
#define RIGHT_SERVO   8
#define LEFT_HELIX_A  6
#define LEFT_HELIX_B  9
#define RIGHT_HELIX_A 3
#define RIGHT_HELIX_B 5

BaloonBot * bot;
SerialReader controller;

void setup()  {
	Serial.begin(9600);
	bot = new BaloonBot(LEFT_SERVO, RIGHT_SERVO, LEFT_HELIX_A, LEFT_HELIX_B, RIGHT_HELIX_A, RIGHT_HELIX_B);
}

void loop()  {
	if (controller.available() > 0) {
		char * cmd = controller.readCommand();
		if (cmd[0]=='R') {
			bot->rotateRight();
		}
		else
		if (cmd[0]=='L') {
			bot->rotateLeft();
		}
		else
		if (cmd[0]=='U') {
			bot->moveUp();
		}
		else
		if (cmd[0]=='D') {
			bot->moveDown();
		}
		free(cmd);
	}
} 

