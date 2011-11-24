#include <Stepper.h>

int pot[10];

// change this to the number of steps on your motor
#define STEPS 200

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);

// the previous reading from the analog input
int previous = 0;

void setup()
{
  // set the speed of the motor 
  stepper.setSpeed(200);
  Serial.begin(9600);
  Serial.println("init");
}

void loop()
{

  //averaging the last values to suppress clutter 
  int sum = 0;
  for (int i= 0; i<9; i ++)
  {
    pot[i]= pot[i+1];
    sum = sum + pot[i];
  }
  // get the sensor value
  pot[9] = analogRead(0);
  sum = sum+pot[9];
  int diff = sum / STEPS;
  Serial.print(pot[9]);Serial.print("\t");
  Serial.print(diff);Serial.print("\t");
  int val = previous - diff;
  Serial.println(val);  
  stepper.step(val);  
  // remember the previous value of the sensor
  previous = diff;
}

