#include <Servo.h>

Servo neck;

int xPos=0;

void setup()  {
  Serial.begin(9600);
  neck.attach(7);
  neck.write(180);
}

void loop()  {
  if(Serial.available() >0)  {
    xPos=Serial.read();
  }
  int xServo = xPos; //map(xPos, 0, 320, 20, 70);
  neck.write(xServo);
} 
