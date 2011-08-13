#include <IRremote.h>

int RECV_PIN = 11;

IRsend irsend;

long decode();

void setup()
{
	Serial.begin(9600);
}

void loop() {
	irsend.sendSony(3, 32);
	delay(1000);

}
