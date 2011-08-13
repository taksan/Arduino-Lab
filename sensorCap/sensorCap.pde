#include <CapSense.h>
#include "led.h"

#define SAMPLES 3
#define ACTIVATION_THRESHOLD 2000

CapSense button = CapSense(2, 3);
Led led = Led(13);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int senseValue = button.capSense(SAMPLES);
	Serial.println(senseValue);
	if (senseValue > ACTIVATION_THRESHOLD) { 
		led.turnOn();
	}
	else {
		led.turnOff();
	}
}
