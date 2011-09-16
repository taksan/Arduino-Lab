#include "PaperBot.h"
#include "led.h"
#include "joy.h"
#include "WalkingGame.h"
#include "NunchuckRx.h"
#include "FollowTheLightGame.h"
#include "LightDirectionDetector.h"
#include "ArduinoApiImpl.h"

#define NUNCHUCK_RX_PIN 7
#define LEFT_LED_PIN 5
#define RIGH_LED_PIN 6

#define GAME_COUNT 2

Joy * joy;
BotGame * games[GAME_COUNT];

Led gameLed(13);
int8_t currentGameNumber;
LightDirectionDetector * lightFollow;

void setup()
{
	Serial.begin(9600);
	Serial.println("------o");
	PaperBot * bot = new PaperBot(9,10);

	joy = new Joy(new NunchuckRx(NUNCHUCK_RX_PIN));

	Serial.println("joy started");

	games[0] = new WalkingGame(bot,joy);

	ArduinoApi * api = new ArduinoApiImpl();
	lightFollow = new LightDirectionDetector(new Eye(api, 2),new Eye(api, 1));
	games[1] = new FollowTheLightGame(bot, lightFollow, LEFT_LED_PIN, RIGH_LED_PIN);

	currentGameNumber = 1;
}

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

long prevCount=0;
long before, now;
void loop()
{
	joy->update();
	if (joy->zPressed()) {
		currentGameNumber = (currentGameNumber + 1) % GAME_COUNT;
	}
	
	updateGameLed();
	games[currentGameNumber]->tick();
}
