class Led {
public:
  Led(int ledPin) {
    this->ledPin = ledPin;
    prepare();
  }
  
  void prepare() {
    pinMode(ledPin,OUTPUT);
  }
  
  void turnOn() {
     digitalWrite(ledPin, HIGH);
  }
  
  void turnOff() {
    digitalWrite(ledPin, LOW);
  }
  
  long ledOnExpirationTime;
  void turnOnAndHoldUntilExpired(int timeToHold) {
    turnOn();
    ledOnExpirationTime = millis() + timeToHold;  
  }

  void turnOffIfTimeExpired() {
    if (millis() < ledOnExpirationTime) 
      return;
    turnOff();    
  }

private:
  int ledPin;
};

