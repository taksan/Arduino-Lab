#ifndef ARDUINO__API__H
#define ARDUINO__API__H

class ArduinoApi {
public:
	virtual int _analogRead(int inputPin) = 0;
};

#endif
