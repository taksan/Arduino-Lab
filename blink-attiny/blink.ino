#include <Servo.h>
#define LED 0


Servo servo;
void setup()
{
  pinMode(LED,OUTPUT);
  servo.attach(7);
  servo.write(90);
}

int angle = 0;
int direction = 1;
void loop()
{
  digitalWrite(LED, HIGH);
  delay(100);

  digitalWrite(LED, LOW);
  delay(100);  

  if (angle >= 90 || angle <= 0)
  	direction = -direction;

  angle += direction;
}
