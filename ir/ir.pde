#include <IRremote.h>

#define  RECV_PIN  11

class IRreceiver {
public:
	IRrecv irrecv;
	boolean enabled;

	IRreceiver(int pin):irrecv(pin){
		enabled = false;
	}

	long decode() {
		if (!enabled) {
			irrecv.enableIRIn();
			enabled = true;
		}
		decode_results results;
		if (irrecv.decode(&results)) {
			irrecv.resume(); 
			return results.value;
		}
		return -1;
	}	
};
IRreceiver rec(RECV_PIN);


void setup()
{
	Serial.begin(9600);
//	rec.irrecv.enableIRIn(); // inicia o receiver
}

void loop() {
	long value = rec.decode();
	if (value != -1)
		Serial.println(value, HEX);
}

