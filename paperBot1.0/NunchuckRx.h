#ifndef NUNCHUCK_RX__H__
#define NUNCHUCK_RX__H__

#include "../NunchuckParams.h"
#include <VirtualWire.h>

class NunchuckRx : public NunchuckInterface {
public:
	NunchuckRx(int commPin) {
		this->commPin = commPin;
		this->buflen = VW_MAX_MESSAGE_LEN;
		this->receivedParams = (NunchuckParams*)buf;
	}

	void begin() {
		int boundRate = 2000;
		vw_set_ptt_inverted(true);
		vw_setup(boundRate);
		vw_set_rx_pin(commPin);
		vw_rx_start(); 
		update();
	}

	void update() {
		if (vw_get_message(buf, &buflen)) // check to see if anything has been received
		{   
			NunchuckParams * p = (NunchuckParams*)buf;
			if (buflen == sizeof(NunchuckParams)) {
				printDebugInfo();
			}
		}
	}

	int readJoyX() {
		return receivedParams->x;
	}

	int readJoyY() {
		return receivedParams->y;
	}
	boolean cPressed() {
		return receivedParams->c;
	}

	boolean zPressed() {
		return receivedParams->z;
	}

	int readAccelX() {
		return receivedParams->ax;
	}

	int readAccelY() {
		return receivedParams->ay;
	}

	int readAccelZ() {
		return receivedParams->az;
	}

private:
	void printDebugInfo()
	{
		char msg[80];
		sprintf(msg, 
				"x=%d y=%d c=%d z=%d ax=%d ay=%d az=%d",
				receivedParams->x,
				receivedParams->y,
				receivedParams->c,
				receivedParams->z,
				receivedParams->ax,
				receivedParams->ay,
				receivedParams->az
			   );
		Serial.println(msg);
	}

	int commPin;
	NunchuckParams * receivedParams;
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen;
};

#endif

