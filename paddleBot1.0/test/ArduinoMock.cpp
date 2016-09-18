#include "ArduinoMock.h"

SerialClass Serial;

int millis_time = 0;

int millis() {
 	return millis_time;
}

void forward_time(int by) {
	millis_time+=by;
}

void defaultWriteCallback(int){ 
}
