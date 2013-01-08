#include <Arduino.h>
#include "common.h"

class Button {
  long lastPushedTime;
  int minTimeBetweenPushes;
public:
  Button(int aButtonPin) {
    buttonWasPressed = false;
    buttonPin = aButtonPin;
    lastPushedTime=0;
    minTimeBetweenPushes = BUTTON_MIN_DELAY;
    
    pinMode(buttonPin,INPUT);
  }
  
  boolean isPressed()
  {
    return digitalRead(buttonPin);
  }
    
  boolean wasPushed() {
    int buttonIsPressed = isPressed();

    if (buttonIsPressed) {
       if (isTimeElapsedSinceLastPushSmallerThanMinimum())
         return false;
       
       buttonWasPressed = true;
       return false;
    }
    
    if (buttonWasPressed) {
        buttonWasPressed = false;
        return true;
    }

    return false;
  }
  
  boolean isTimeElapsedSinceLastPushSmallerThanMinimum() 
  {
       long timeElapsedSinceLastPush = millis() -lastPushedTime;
       if (lastPushedTime!=0 && timeElapsedSinceLastPush<minTimeBetweenPushes){
          return true;
       }
       lastPushedTime = millis();
       return false;
  }
private:
  boolean buttonWasPressed;
  int buttonPin;
};
