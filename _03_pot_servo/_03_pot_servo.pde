#include <Servo.h>

Servo motor;
void setup()
{
  motor.attach(7);
}

void loop()
{
  int potLevel = analogRead(0);
  int angulo = potLevel/1024.0 * 180;
  motor.write(angulo);
}
