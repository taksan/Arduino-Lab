#include "TxNunchuck.h"

TxNunchuck * txNunchuck;
void setup()
{
	Serial.begin(9600);
	txNunchuck = new TxNunchuck(3);
}

void loop()
{
   txNunchuck->update();
}
