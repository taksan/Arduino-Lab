#include "../NunchuckParams.h"
#include <Nunchuck.h>
#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#include <SerialDebug.h>
#undef int
#undef abs
#undef double
#undef float
#undef round


class TxNunchuck {
public:
	TxNunchuck(int txPort)
	{
		int boundRate = 2000;

		vw_set_ptt_inverted(true); 
		vw_setup(boundRate);
		vw_set_tx_pin(txPort);
		nunchuck.begin();
	}

	void update()
	{
		nunchuck.update();
		char nunchuckParams[60];
		NunchuckParams p;
		p.x = nunchuck.readJoyX();
		p.y = nunchuck.readJoyY();
		p.c = nunchuck.cPressed();
		p.z = nunchuck.zPressed();
		p.ax = nunchuck.readAccelX();
		p.ay = nunchuck.readAccelY();
		p.az = nunchuck.readAccelZ();

		vw_send((uint8_t *)&p, sizeof(p));
		vw_wait_tx();

		sprintf(nunchuckParams, 
				"x=%d y=%d c=%d z=%d ax=%d ay=%d az=%d",
				nunchuck.readJoyX(),
				nunchuck.readJoyY(),
				nunchuck.cPressed(),
				nunchuck.zPressed(),
				nunchuck.readAccelX(),
				nunchuck.readAccelY(),
				nunchuck.readAccelZ()
			   );

		Serial.print("Sender : ");
		Serial.println(nunchuckParams);
	}
private:
	Nunchuck nunchuck;
};
