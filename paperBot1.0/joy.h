#ifndef JOY__H__
#define JOY__H__

#include "NunchuckInterface.h"
#include "../NunchuckParams.h"

class Joy {
public:
	Joy(NunchuckInterface * nunchuck){
		this->nunchuck = nunchuck;
		this->nunchuck->begin();

		baseX = this->nunchuck->readJoyX();
		baseY = this->nunchuck->readJoyY();
	}

	long lastPrint;
	void update() {
		nunchuck->update();
		
		jY = nunchuck->readJoyY();
		jX = nunchuck->readJoyX();

		ensureOnlyASingleMovementIsConsidered();
	}

	boolean upJoy() {
		return isRelevant(jY, baseY);
	}

	boolean downJoy() {
		return isRelevant(baseY, jY);
	}

	boolean leftJoy() {
		return isRelevant(baseX, jX);
	}

	boolean rightJoy() {
		return isRelevant(jX, baseX);
	}

	boolean cPressed() {
		return nunchuck->cPressed();
	}

	boolean zPressed() {
		return nunchuck->zPressed();
	}

private:
	void ensureOnlyASingleMovementIsConsidered() {
		if (ABS(jY-baseY) > ABS(jX-baseX)) {
			neutralizeXAxis();
		}
		else {
			neutralizeYAxis();
		}
	}

	inline void neutralizeXAxis() {
		jX = baseX;
	}
	inline void neutralizeYAxis() {
		jY = baseY;
	}

	inline boolean isRelevant(int op1, int op2) {
		int intensity = op1-op2;
		return intensity > 10;
	}

	NunchuckInterface * nunchuck;

	int baseX;
	int baseY;
	int jX, jY;
};

#endif
