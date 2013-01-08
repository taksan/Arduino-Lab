#ifndef ARDUINO__API__IMPL__H
#define ARDUINO__API__IMPL__H
#include <Arduino.h>

#include "ArduinoApi.h"

class ArduinoApiImpl: public ArduinoApi {
public:
	int _analogRead(int inputPin){
		return analogRead(inputPin);
	}

	void _delay(int ms) {
		delay(ms);
	}
};

#endif
