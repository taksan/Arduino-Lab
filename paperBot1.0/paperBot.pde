#include <Nunchuck.h>
#include "PaperBot.h"
#include "led.h"
#include "joy.h"
#include "WalkingGame.h"
#include "MaintenanceGame.h"
#include "NunchuckHw.h"
//#include "NunchuckRx.h"

#define NUNCHUCK_RX_PIN 7

Joy * joy;

WalkingGame * walking;
MaintenanceGame * maintenance;
BotGame * currentGame;

Led maintenanceLed(13);
boolean isInMaintenance = false;

void setup()
{
	Serial.begin(9600);
	Serial.println("------");

	PaperBot * bot = new PaperBot(9, 10);
//	joy = new Joy(new NunchuckRx(NUNCHUCK_RX_PIN));
	joy = new Joy(new NunchuckHw());
	walking = new WalkingGame(bot,joy);
	maintenance = new MaintenanceGame(bot,joy);
	currentGame = walking;
}

void loop()
{
	joy->update();
	if (joy->zPressed()) {
		isInMaintenance = !isInMaintenance;
		if (isInMaintenance) {
			Serial.println("Switched to maintenance");
			maintenanceLed.turnOn();
			currentGame = maintenance;
		}
		else {	
			Serial.println("Switched to walking mode");
			maintenanceLed.turnOff();
			currentGame = walking;
		}
	}

	currentGame->tick();
}

