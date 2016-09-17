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

		baseX = this->nunchuck->readJoyX();
		Serial.println("1");
		baseY = this->nunchuck->readJoyY();
		Serial.println("2");
		SerialDebug::println("Base joy axis values bx %d by %d", baseX, baseY);
		jY = baseY;
		jX = baseX;
		SerialDebug::println("initial values jX=%d jY=%d", jX, jY);
		lastMoveIntensity = 0;
		wasUpdated = false;
	}

	void update() {
		wasUpdated = nunchuck->update();
		jY = nunchuck->readJoyY();
		jX = nunchuck->readJoyX();

		ensureOnlyASingleMovementIsConsidered();
	}

	int16_t getLastMoveIntensity() {
		return lastMoveIntensity;
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

	bool wasUpdated;
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

	inline boolean isRelevant(int16_t op1, int16_t op2) {
		int16_t intensity = ABS(op1-op2);
		bool relevant = intensity > 10;
		if (relevant)
			lastMoveIntensity = intensity;
		return relevant;
	}

	NunchuckInterface * nunchuck;

	int16_t baseX;
	int16_t baseY;
	int16_t jX, jY;
	int16_t lastMoveIntensity;
};

#endif
