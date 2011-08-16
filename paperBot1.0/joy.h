#ifndef JOY__H__
#define JOY__H__

#include "NunchuckInterface.h"

class Joy {
public:
	Joy(NunchuckInterface * nunchuck){
		this->nunchuck = nunchuck;
		this->nunchuck->begin();
		baseX = this->nunchuck->readJoyX();
		baseY = this->nunchuck->readJoyY();
	}

	void update() {
		nunchuck->update();
	}

	boolean upJoy() {
		int y = nunchuck->readJoyY();
		int intensity = y - baseY;

		return isRelevant(intensity);
	}

	boolean downJoy() {
		int y = nunchuck->readJoyY();
		int intensity = baseY - y;

		return isRelevant(intensity);
	}

	boolean leftJoy() {
		int x = nunchuck->readJoyX();
		int intensity = baseX - x;

		return isRelevant(intensity);
	}

	boolean rightJoy() {
		int x = nunchuck->readJoyX();
		int intensity = x - baseX;
		return isRelevant(intensity);
	}

	boolean cPressed() {
		return nunchuck->cPressed();
	}

	boolean zPressed() {
		return nunchuck->zPressed();
	}

private:
	boolean isRelevant(int intensity) {
		return intensity > 5;
	}

	NunchuckInterface * nunchuck;

	int baseX;
	int baseY;
};

#endif
