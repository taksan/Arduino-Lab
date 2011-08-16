#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round

#define TX_PIN 3

void setup()
{
	Serial.begin(9600);
	Serial.println("This is the test app for TX. Type to send to RX");
	Serial.print(">");

	// Initialise the IO and ISR
	vw_set_ptt_inverted(true); // Required for RF Link module
	vw_setup(2000);                 // Bits per sec
	vw_set_tx_pin(TX_PIN);                // pin 3 is used as the transmit data out into the TX Link module, change this to suit your needs.
}

void loop()
{
	char buffer[40];
	static int pos=0;

	if (Serial.available() > 0) {
		int count = Serial.available();
		boolean sendMessage = false;
		for (int i=0; i < count && pos < 39; i++, pos++) {
			buffer[pos] = Serial.read();
			if(buffer[pos] == 13) {
				pos++;
				buffer[pos] = 0;
				sendMessage = true;
				pos = 0;
				Serial.println();
				break;
			}
			Serial.print(buffer[pos]);
		}
		if (pos == 39) {
			buffer[pos]=0;
			sendMessage=true;
			pos=0;
		}
		if (sendMessage) {
			vw_send((uint8_t *)buffer, strlen(buffer));
			vw_wait_tx();                                          // Wait for message to finish
			Serial.print("> ");
		}
	}
}
