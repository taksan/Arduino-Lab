#include <Nunchuck.h>
#include <Servo.h>
#include "PaperBot.h"
#include "led.h"
#include "joy.h"

PaperBot * bot;
Joy * joy;
long lastMove;

Angle dirAngle;
Angle thrustAngle;


void setup()
{
	Serial.begin(9600);
	Serial.println("------");
	bot = new PaperBot(9, 10);
	joy = new Joy();
	lastMove = micros();
}


Led maintenanceLed(13);
void maintenanceLoop();
void walkingLoop();
boolean isInMaintenance = false;

void loop()
{
	joy->update();
	if (joy->zPressed()) {
		isInMaintenance = !isInMaintenance;
	}
	if (isInMaintenance) {
		maintenanceLoop();
	}
	else {
		walkingLoop();
	}
}

void walkingLoop()
{
	maintenanceLed.turnOn();	
	if (joy->upJoy()) {
		bot->stepAhead();
	}
	if (joy->downJoy()) {
		bot->stepBack();
	}
}

void maintenanceLoop()
{
	maintenanceLed.turnOnAndHoldUntilExpired(200);
	if (joy->upJoy()) {
		thrustAngle.inc();
	}
	if (joy->downJoy()) {
		thrustAngle.dec();
	}

	if (joy->rightJoy()) {
		dirAngle.inc();
	}
	if (joy->leftJoy()) {
		dirAngle.dec();
	}
	if (joy->cPressed()) {
		Serial.println(dirAngle.get());
		Serial.println(thrustAngle.get());
	}

	bot->setDirection(dirAngle.get());
	bot->setThrust(thrustAngle.get());
	delay(20);
}


