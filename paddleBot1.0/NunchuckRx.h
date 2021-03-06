#ifndef NUNCHUCK_RX__H__
#define NUNCHUCK_RX__H__

#include "../NunchuckParams.h"
#include <VirtualWire.h>
#include "SerialDebug.h"

class NunchuckRx : public NunchuckInterface {
public:
	NunchuckRx(int commPin) {
		this->commPin = commPin;
		this->buflen = VW_MAX_MESSAGE_LEN;
		this->ready = false;
		this->badMessageCount = 0;
		this->resyncNeed = false;
	}

	void begin() {
		Serial.println("Begin rx nunchuck configuration");
		int boundRate = 2000;
		vw_set_ptt_inverted(true);
		vw_setup(boundRate);
		vw_set_rx_pin(commPin);
		vw_rx_start(); 

	}

	bool update()
	{
		if (resyncPerformed()) 
			return false;

		bool result = updateReturnTrueIfNewData();
		if (!result) {
			if (badMessageCount > 5) {
				resyncNeed = true;
				vw_rx_stop();
				return false;
			}
		}
		badMessageCount = 0;

		if (!ready && result) {
			Serial.println("First data received");
			ready = true;
		}
		return result;
	}

	bool isReady() {
		return ready;
	}

	int readJoyX() {
		return receivedParams.x;
	}

	int readJoyY() {
		return receivedParams.y;
	}

	boolean cPressed() {
		boolean pressed = receivedParams.c;
		receivedParams.c = false;

		return pressed;
	}

	boolean zPressed() {
		boolean pressed = receivedParams.z;
		receivedParams.z = false;

		return pressed;
	}

	int readAccelX() {
		return receivedParams.ax;
	}

	int readAccelY() {
		return receivedParams.ay;
	}

	int readAccelZ() {
		return receivedParams.az;
	}

private:
	boolean updateReturnTrueIfNewData() {
		if (vw_get_message(buf, &buflen)) // check to see if anything has been received
		{   
			if (buflen == sizeof(NunchuckParams)) {
				memcpy(&receivedParams, buf, sizeof(receivedParams));
				//printDebugInfo();
				return true;
			}
			Serial.println("bogus data received, ignored");
			badMessageCount++;
		}
		return false;
	}

	void restart() {
		if (badMessageCount > 5) {
			resyncNeed = true;
		}
	}

	void printDebugInfo()
	{
		SerialDebug::println(
				"Rx data: x=%d y=%d c=%d z=%d ax=%d ay=%d az=%d",
				receivedParams.x,
				receivedParams.y,
				receivedParams.c,
				receivedParams.z,
				receivedParams.ax,
				receivedParams.ay,
				receivedParams.az
			   );
	}

	bool resyncPerformed() {
		if (!resyncNeed) 
			return false;
		Serial.println("Communication corrupted. Trying to reboot comm.");
		badMessageCount = 0;
		begin();
		return true;
	}

	bool needsResync() {
		if (badMessageCount < 5)
			return false;


		Serial.println("Communication corrupted. Trying to reboot comm.");
		resyncNeed = true;
		vw_rx_stop();
		return false;
	}

	int commPin;
	NunchuckParams receivedParams;
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen;
	bool ready;
	uint8_t badMessageCount;
	bool resyncNeed;
};

#endif

