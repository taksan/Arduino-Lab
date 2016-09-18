#ifndef SERVO__TIMER2__H__
#define SERVO__TIMER2__H__

class ServoTimer2
{
  public:
	// constructor:
	ServoTimer2(){};

	uint8_t attach(int){}
	uint8_t attach(int, int, int){}
    void detach(){}
    void write(int){}
    int read(){}
	boolean attached(){}
};

#endif
