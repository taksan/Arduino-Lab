#include "PaperBot.h"
#include "led.h"
#include "joy.h"
#include "WalkingGame.h"
#include "NunchuckRx.h"
#include "FollowTheLightGame.h"
#include "LightDirectionDetector.h"
#include "ArduinoApiImpl.h"
#include "LightFollower.h"

#define NUNCHUCK_RX_PIN 7
#define LEFT_LED_PIN 5
#define RIGH_LED_PIN 6

#define GAME_COUNT 2

Joy * joy = NULL;
BotGame * games[GAME_COUNT];

Led gameLed(13);
Led tickLed(12);
int8_t currentGameNumber;
LightDirectionDetector * lightFollow;

void updateGameLed() {
	switch(currentGameNumber) {
	case 0:
		gameLed.turnOn();
		break;
	case 1:
		gameLed.turnOff();
		break;
	}
}

Servo * thrustMotor;
Servo * directionMotor;
void setup()
{
	Serial.begin(9600);
	Serial.println("Starting up...");

	PaperBot * bot = new PaperBot(9,10);

	joy = new Joy(new NunchuckRx(NUNCHUCK_RX_PIN));
	games[0] = new WalkingGame(bot,joy);

	ArduinoApi * api = new ArduinoApiImpl();
	lightFollow = new LightDirectionDetector(new LightFollower(bot), new Eye(api, 2),new Eye(api, 1));
	games[1] = new FollowTheLightGame(bot, lightFollow, LEFT_LED_PIN, RIGH_LED_PIN);

	currentGameNumber = 0;


	Serial.println("Rx Nunchuck Started. Turn the led on");
	updateGameLed();
}

long prevCount=0;
long before, now;
void loop()
{
	int32_t before = millis();
	joy->update();
	if (joy->zPressed()) {
		currentGameNumber = (currentGameNumber + 1) % GAME_COUNT;
	}
	if (joy->wasUpdated) {
		gameLed.toggle();
	}
	
//	updateGameLed();
	games[currentGameNumber]->tick();
	tickLed.blink(500);
}
