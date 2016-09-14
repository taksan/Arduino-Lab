#include <Servo.h>
#include <Wire.h>
#include <Nunchuck.h>

Nunchuck nunchuck;
Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  nunchuck.begin();
}

void loop() {
    nunchuck.update(); 

    if (nunchuck.readZ()) {
        servo1.write(nunchuck.readAngleX());
        servo2.write(nunchuck.readAngleY());
    }

    if (nunchuck.readC()) {
        servo1.write(map(nunchuck.readJoyX(), 5, 250, 0, 180));
        servo2.write(map(nunchuck.readJoyY(), 5, 250, 0, 180));
    }

    delay(10);
}

