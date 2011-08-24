#include <Nunchuck.h>
#include "PaperBot.h"
#include "led.h"
#include "joy.h"
#include "WalkingGame.h"
#include "MaintenanceGame.h"
#include "NunchuckRx.h"
#include "LightDirectionDetector.h"
#include "ArduinoApiImpl.h"

#define NUNCHUCK_RX_PIN 7

Joy * joy;

WalkingGame * walking;
MaintenanceGame * maintenance;
BotGame * currentGame;

Led maintenanceLed(13);
boolean isInMaintenance = false;
LightDirectionDetector * lightFollow;

void setup()
{
	Serial.begin(9600);
	Serial.println("------o");
#if 0
	PaperBot * bot = new PaperBot(9, 10);
	joy = new Joy(new NunchuckRx(NUNCHUCK_RX_PIN));
	walking = new WalkingGame(bot,joy);
	maintenance = new MaintenanceGame(bot,joy);
	currentGame = walking;
#endif
	ArduinoApi * api = new ArduinoApiImpl();
	lightFollow = new LightDirectionDetector(new Eye(api, 2),new Eye(api, 1));
}

void loop()
{
	lightFollow->update();
	LightDirectionDetector::Direction directionToGo = lightFollow->getDirectionToGo();
	if (directionToGo == LightDirectionDetector::turnLeft) {
		Serial.println("go left!");
	}

	if (directionToGo == LightDirectionDetector::turnRight) {
		Serial.println("go right!");
	}

	if (directionToGo == LightDirectionDetector::goAhead) {
		Serial.println("go ahead");
	}

	delay(500);
	return;
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

