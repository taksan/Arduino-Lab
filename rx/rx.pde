#include "../NunchuckParams.h"
#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder

#define RX_PIN 7


void setup()
{
	Serial.begin(9600);    
	Serial.println("RX kicking in");

	// Initialise the IO and ISR
	vw_set_ptt_inverted(true);    // Required for RX Link Module
	vw_setup(2000);                   // Bits per sec
	vw_set_rx_pin(RX_PIN);           // We will be receiving on pin 23 (Mega) ie the RX pin from the module connects to this pin.
	vw_rx_start();                      // Start the receiver
}

void loop()
{
//	delay(1000);
//	Serial.println(tcounter,DEC);
//	return;

	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	if (vw_get_message(buf, &buflen)) // check to see if anything has been received
	{
		NunchuckParams * p = (NunchuckParams*)buf;
		if (buflen == sizeof(NunchuckParams)) {
			char msg[80];
			sprintf(msg, 
				"[%d / %d] x=%d y=%d c=%d z=%d ax=%d ay=%d az=%d",
				buflen, sizeof(NunchuckParams),
				p->x,
				p->y,
				p->c,
				p->z,
				p->ax,
				p->ay,
				p->az
				);
			Serial.println(msg);
		}
		else {
			int i;
			// Message with a good checksum received.

			for (i = 0; i < buflen; i++)
			{
				Serial.print(buf[i]);  // the received data is stored in buffer
			}
			Serial.println("");
		}
	}
}
