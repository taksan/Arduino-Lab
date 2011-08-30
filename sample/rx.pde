#include <inttypes.h>
#include <FrequencyTimer2.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder

void handler()
{
	Serial.print(".");
}

void setup()
{
	Serial.begin(9600);    
	FrequencyTimer2::setPeriod(50);
	FrequencyTimer2::setOnOverflow(handler);
}

void loop()
{
}
