#include "TxNunchuck.h"

RFNunchuck * rfNunchuck;
void setup()
{
	Serial.begin(9600);
	rfNunchuck = new RFNunchuck(3);
}

void loop()
{
   rfNunchuck->update();
   delay(200);
}
