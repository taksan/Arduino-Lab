#include <Wire.h>
#include <Nunchuck.h>

Nunchuck nunchuck;

void setup() {
  Serial.begin(9600);
  nunchuck.begin();
}

void loop() {
    nunchuck.update(); 

    Serial.print(": ");  
    Serial.print(nunchuck.readAngleX(), DEC);
    Serial.print(", ");  
    Serial.print(nunchuck.readAngleY(), DEC);
    Serial.print(", ");  
    Serial.print(nunchuck.readAngleZ(), DEC);
    Serial.print(" - ");  
    Serial.print(nunchuck.readC(), DEC); 
    Serial.print(", ");  
    Serial.print(nunchuck.readZ(), DEC); 
    Serial.print(" - ");  
    Serial.print(nunchuck.readJoyX(), DEC); 
    Serial.print(", ");  
    Serial.print(nunchuck.readJoyY(), DEC); 

    Serial.println();

	delay(20);  
}




