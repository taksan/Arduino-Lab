
#include <ServoTimer2.h>


ServoTimer2 servo1;

void setup()
{
	servo1.attach(10);
}

void loop() {
	servo1.write(0);
}

