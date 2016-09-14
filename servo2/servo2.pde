
#include <ServoTimer2.h>


ServoTimer2 horiz, vert;

int horizPos=20, vertPos=0;

void setup()  {
	Serial.begin(9600);
	horiz.attach(9);
	vert.attach(10);

	horizPos = map(horizPos, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	horiz.write(20);
	vert.write(vertPos);

}

// this function just increments a value until it reaches a maximum 
int incPulse(int val, int inc){
   if( val + inc  > MAX_PULSE_WIDTH )
      return MIN_PULSE_WIDTH;
   else
      return val + inc;  
}


void loop()  {
	delay(10);
//	horizPos = (horizPos + 1)%90;
	vertPos = (vertPos + 1)%180;
	if (vertPos == 0)
		delay(1000);
//	horiz.write(horizPos);
//	vertPos = incPulse(vertPos, 1);
	int micro = map(vertPos, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);

	vert.write(vertPos);
	char res[255];
	sprintf(res, "(angle %d) - %d\r\n", vertPos, vert.read());
	Serial.write(res);

} 

