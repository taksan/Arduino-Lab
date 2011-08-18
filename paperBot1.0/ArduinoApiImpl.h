#ifndef ARDUINO__API__IMPL__H
#define ARDUINO__API__IMPL__H
#include <WProgram.h>

#include "ArduinoApi.h"

class ArduinoApiImpl: public ArduinoApi {
public:
	int _analogRead(int inputPin){
		return analogRead(inputPin);
	}
};

#endif
