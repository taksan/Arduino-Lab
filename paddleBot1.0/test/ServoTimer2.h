#ifndef SERVO__TIMER__H__
#define SERVO__TIMER__H__

#include "ArduinoMock.h"

class ServoTimer2
{
	public:
		// constructor:
		ServoTimer2(){
			writecallback = NULL;
		};

		uint8_t attach(int){}
		uint8_t attach(int, int, int){}
		void detach(){}
		int read(){}
		boolean attached(){}


		void write(int value){
			if (writecallback)
				writecallback(value);
		}

		void (*writecallback)(int);
};

#endif 
