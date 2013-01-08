#include <Arduino.h>

class Buzzer{

	int port;
	long expirationTime;
	long toneDuration;
	long toneExpirationTimeUs;
	boolean isBuzzing;

	public:
	Buzzer(int aPort){
		port = aPort;
		expirationTime = 0;
		toneExpirationTimeUs = 0;
		toneDuration = 1;
		isBuzzing = false;
		initPort();
	}

	void beepFor(int milliseconds){
		expirationTime = millis() + milliseconds;
		startBuzzing();
	}

	void playTone(long frequencyInHz, int milliseconds) {
		long oneSecondInUs = 1000000;
		toneDuration = (oneSecondInUs/frequencyInHz) / 2;
		resetToneExpirationTime();
		beepFor(milliseconds);
	}


	boolean tick(){
		if (millis() > expirationTime){
			stopBuzzing();
			return false;
		}

		boolean isPlaying = true;
		if (micros() > toneExpirationTimeUs){
			if (isBuzzing) {
				stopBuzzing();
			}
			else {
				startBuzzing();
			}

			resetToneExpirationTime();
		}
		return isPlaying;
	}

	private:

	void resetToneExpirationTime(){
		toneExpirationTimeUs = micros() + toneDuration;
	}

	void initPort() {
		pinMode(port, OUTPUT);
	}

	void startBuzzing() {
		digitalWrite(port, HIGH);
		isBuzzing = true;
	}  

	void stopBuzzing() {
		digitalWrite(port, LOW);
		isBuzzing = false;
	}
};

