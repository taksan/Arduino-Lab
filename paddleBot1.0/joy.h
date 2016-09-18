#ifndef JOY__H__
#define JOY__H__

#include "NunchuckInterface.h"
#include "../NunchuckParams.h"
#include "SerialDebug.h"

class Joy {
public:
	Joy(NunchuckInterface * nunchuck){
		this->nunchuck = nunchuck;
		this->nunchuck->begin();
		lastMoveIntensity = 0;
		wasUpdated = false;
		initialized = false;
	}

	bool update() {
		wasUpdated = nunchuck->update();
		if (!nunchuck->isReady()) return false;

		if (!initialized)
			this->initialize();
		
		jY = nunchuck->readJoyY();
		jX = nunchuck->readJoyX();

		ensureOnlyASingleMovementIsConsidered();
		return true;
	}

	int16_t getLastMoveIntensity() {
		return lastMoveIntensity;
	}

	boolean upJoy() {
		return jY>baseY && isRelevant(jY, baseY);
	}

	boolean downJoy() {
		return baseY>jY && isRelevant(baseY, jY);
	}

	boolean leftJoy() {
		return baseX>jX && isRelevant(baseX, jX);
	}

	boolean rightJoy() {
		return jX>baseX && isRelevant(jX, baseX);
	}

	boolean cPressed() {
		return nunchuck->cPressed();
	}

	boolean zPressed() {
		return nunchuck->zPressed();
	}

	bool wasUpdated;
private:
	void initialize() {
		baseX = this->nunchuck->readJoyX();
		baseY = this->nunchuck->readJoyY();
		SerialDebug::println("Base joy axis values bx %d by %d", baseX, baseY);
		jY = baseY;
		jX = baseX;
		SerialDebug::println("initial values jX=%d jY=%d", jX, jY);
		initialized = true;
	}
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

	inline boolean isRelevant(int16_t op1, int16_t op2) {
		int16_t intensity = ABS(op1-op2);
		bool relevant = intensity > 10;
		if (relevant) {
			lastMoveIntensity = MIN(intensity,100);
//			SerialDebug::println("isRelevant: op1: %d op2: %d i: %d", op1, op2, lastMoveIntensity);
		}
		return relevant;
	}

	NunchuckInterface * nunchuck;

	int16_t baseX;
	int16_t baseY;
	int16_t jX, jY;
	int16_t lastMoveIntensity;
	bool initialized;
};

#endif
