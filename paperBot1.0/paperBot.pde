#include "PaperBot.h"
#include "led.h"
#include "joy.h"
#include "WalkingGame.h"
#include "MaintenanceGame.h"
#include "FollowTheLightGame.h"
#include "NunchuckRx.h"
#include "LightDirectionDetector.h"
#include "ArduinoApiImpl.h"

#define NUNCHUCK_RX_PIN 7

Joy * joy;

WalkingGame * walking;
MaintenanceGame * maintenance;
FollowTheLightGame * followTheLightGame;
BotGame * currentGame;

Led maintenanceLed(13);
boolean isInMaintenance = false;
LightDirectionDetector * lightFollow;

void setup()
{
	Serial.begin(9600);
	Serial.println("------o");
	PaperBot * bot = new PaperBot(9, 10);
#if 0
	joy = new Joy(new NunchuckRx(NUNCHUCK_RX_PIN));
	walking = new WalkingGame(bot,joy);
	maintenance = new MaintenanceGame(bot,joy);
	currentGame = walking;
#endif
	ArduinoApi * api = new ArduinoApiImpl();
	lightFollow = new LightDirectionDetector(new Eye(api, 2),new Eye(api, 1));

	followTheLightGame = new FollowTheLightGame(bot, lightFollow);

	currentGame = maintenance;
}

void loop()
{
	currentGame->tick();

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

