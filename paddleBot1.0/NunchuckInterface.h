#ifndef NUNCHUCK__intERFACE__H_
#define NUNCHUCK__intERFACE__H_

class NunchuckInterface {
public:
	virtual void begin() = 0;
	virtual bool update() = 0;
	virtual int readJoyX() = 0;
	virtual int readJoyY() = 0;
	virtual boolean cPressed() = 0;
	virtual boolean zPressed() = 0;
	virtual int readAccelX() = 0;
	virtual int readAccelY() = 0;
	virtual int readAccelZ() = 0;
	virtual bool isReady() = 0;
};

#endif

