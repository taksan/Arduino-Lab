#ifndef NUNCHUCKHW__H__
#define NUNCHUCKHW__H__

#include "Nunchuck.h"


class NunchuckHw : public NunchuckInterface {
public:
	void begin() {
		mNunchuck.begin();
	}

	bool update() {
		mNunchuck.update();
		return true;
	}

	int readJoyX() {
		return mNunchuck.readJoyX();
	}

	int readJoyY() {
		return mNunchuck.readJoyY();
	}
	boolean cPressed() {
		return mNunchuck.cPressed();
	}

	boolean zPressed() {
		return mNunchuck.zPressed();
	}

	int readAccelX() {
		return mNunchuck.readAccelX();
	}

	int readAccelY() {
		return mNunchuck.readAccelY();
	}

	int readAccelZ() {
		return mNunchuck.readAccelZ();
	}

private:
	Nunchuck mNunchuck;
};

#endif

