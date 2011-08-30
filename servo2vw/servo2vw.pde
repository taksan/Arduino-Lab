#include <ServoTimer2.h>
#include <VirtualWire.h>

ServoTimer2 myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 

void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  vw_setup(2000); // Bits per sec
  vw_rx_start();	// Start the receiver PLL running
  myservo.attach(9);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;
    Serial.print("Got: ");
    for (i = 0; i < buflen; i  )
    {
      if(buf[i] == '1')
        {digitalWrite(6, HIGH);}
      else if(buf[i] == '0')
        {digitalWrite(6, LOW);}
      
      if(buf[i] != '0' && buf[i] != '1')
      {
        pos = buf[i];
        pos = map(pos,0,180,0,2000);
      }
      
      Serial.print(buf[i], HEX);
      Serial.print(" ");
      Serial.print(pos,DEC);
    }
    Serial.println("");
  }
  myservo.write(pos);
}
