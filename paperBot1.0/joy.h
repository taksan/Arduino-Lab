#ifndef JOY__H__
#define JOY__H__

#include "NunchuckInterface.h"
#include "../NunchuckParams.h"
#include "SerialDebug.h"

#define MAX_LOOPS_WITHOUT_UPDATE 10

extern bool turnPointMet;
class Joy {
public:
	Joy(NunchuckInterface * nunchuck){
		this->nunchuck = nunchuck;
		this->nunchuck->begin();

		baseX = this->nunchuck->readJoyX();
		baseY = this->nunchuck->readJoyY();
		SerialDebug::println("bx %d by %d", baseX, baseY);
		jY = baseY;
		jX = baseX;
		loopsWithoutUpdate  = 0;
	}

	int loopsWithoutUpdate;
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

	bool ensureDataIsReceivedIfUpdateShortageHappens() {
		loopsWithoutUpdate++;
		if (loopsWithoutUpdate > MAX_LOOPS_WITHOUT_UPDATE) {
			while(!nunchuck->update()) delay(1);
			loopsWithoutUpdate=0;
			return true;
		}
		return false;
	}

	inline void neutralizeXAxis() {
		jX = baseX;
	}
	inline void neutralizeYAxis() {
		jY = baseY;
	}

	inline boolean isRelevant(int op1, int op2) {
		int intensity = op1-op2;
		bool relevant = intensity > 10;
		if (relevant) {
			SerialDebug::println("op-new=%ld op-base=%ld", op1, op2);
		}
		return relevant;
	}

	NunchuckInterface * nunchuck;

	int baseX;
	int baseY;
	int jX, jY;
};

#endif
