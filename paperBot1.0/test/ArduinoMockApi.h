#include "../ArduinoApi.h"

class ArduinoMockApi : public ArduinoApi
{
public:
	ArduinoMockApi(int pinCount) {
		valuesToReturn = new int[pinCount];
	}
		
	~ArduinoMockApi() {
		delete [] valuesToReturn;
	}

	void setNextAnalogValueToReturn(int pin, int value) {
		valuesToReturn[pin] = value;
	}

	int _analogRead(int pin) {
		return valuesToReturn[pin];
	}

private:	
	int  * valuesToReturn;
};

