#ifndef MAINTENANCE_GAME__H
#define MAINTENANCE_GAME__H

#include "BotGame.h"
#include "Angle.h"

class MaintenanceGame : public BotGame
{
public:
	MaintenanceGame(PaperBot * bot, Joy * joy) {
		this->bot = bot;
		this->joy = joy;
		isMoving = false;
	}

	virtual void tick()
	{
		boolean readMove = false;
		if (joy->upJoy()) {
			readMove = true;
			thrustAngle.inc();
		}
		if (joy->downJoy()) {
			readMove = true;
			thrustAngle.dec();
		}

		if (joy->rightJoy()) {
			readMove = true;
			dirAngle.inc();
		}
		if (joy->leftJoy()) {
			readMove = true;
			dirAngle.dec();
		}
		if (joy->cPressed()) {
			printParameters();
		}
		if (isMoving && !readMove) {
			printParameters();
		}
		isMoving = readMove;

		bot->setDirection(dirAngle.get());
		bot->setThrust(thrustAngle.get());
	}

	void printParameters() {
		char msg[40];
		sprintf(msg, "Dir: %d Thrust: %d", dirAngle.get(), thrustAngle.get());
		Serial.println(msg);
	}
private:
	Angle dirAngle;
	Angle thrustAngle;

	boolean isMoving; 
	PaperBot * bot;
	Joy * joy;
};

#endif

