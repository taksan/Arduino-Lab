#ifndef LED__H__
#define LED__H__

class Led {
public:
  Led(int8_t ledPin) {
    this->ledPin = ledPin;
    prepare();
  }
  
  void prepare() {
    pinMode(ledPin,OUTPUT);
	ledOnExpirationTime = millis();
  }
  
  void turnOn() {
     digitalWrite(ledPin, HIGH);
	 ledOn = true;
  }
  
  void turnOff() {
    digitalWrite(ledPin, LOW);
	ledOn = false;
  }
  
  long ledOnExpirationTime;
  void turnOnAndHoldUntilExpired(int16_t timeToHold) {
    turnOn();
    ledOnExpirationTime = millis() + timeToHold;  
  }

  void turnOffIfTimeExpired() {
    if (millis() < ledOnExpirationTime) 
      return;
    turnOff();    
  }

  void blink(int period) {
  	if (millis() < ledOnExpirationTime) {
		return;
	}
  	ledOnExpirationTime = millis() + period;
	if (ledOn) 
		turnOff();
	else 
  		turnOn();
  }

private:
  int8_t ledPin;
  bool ledOn;
};

#endif
