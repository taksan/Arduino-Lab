#ifndef __EYE__H___
#define __EYE__H___

#define STRENGH_THRESHOLD 3

class Eye {
public:
	Eye(ArduinoApi * api, int8_t pin):
		api(api),
		pin(pin),
		adjustFactor(1),
		previousWasStrong(false),
		strenghThreshold(STRENGH_THRESHOLD)
	{
	}

	void gaugeBase() {
		baseLevel = api->_analogRead(pin);
		level = baseLevel;
	}

	void setAdjustFactorAgainst(int16_t otherLevel)
	{
		this->adjustFactor = (float)otherLevel / this->baseLevel;
	}

	void update() {
		previousWasStrong = isStronglyInfluenced();
		updateStrenghThresold();
		level = api->_analogRead(pin);
	}

	bool isStronglyInfluenced() {
		return getIntensity() > strenghThreshold;
	}

	bool isWeaklyInfluenced() {
		return !isStronglyInfluenced();
	}

	bool previousIntensityWasStrong() {
		return previousWasStrong;
	}

	int16_t getIntensity() {
		int16_t levelOffset = level - baseLevel;
		return levelOffset * adjustFactor;
	}

	int16_t getLevel() { 
		return level;
	}

	bool isStrongerThan(Eye * anotherEye) {
		return (this->getIntensity() - strenghThreshold/2) > anotherEye->getIntensity();
	}

private:
	int8_t pin;
	int16_t level;
	int16_t baseLevel;
	float adjustFactor;
	bool previousWasStrong;
	int strenghThreshold;

	ArduinoApi * api;

	void updateStrenghThresold() {
		if (isStronglyInfluenced()) {
			int16_t newThreshold = getIntensity() - 3;
			if (newThreshold > strenghThreshold) {
				strenghThreshold = newThreshold;
				SerialDebug::println("Updating threshold to %d", newThreshold);
			}
		}
		else {
			if (strenghThreshold > STRENGH_THRESHOLD*2) {
				strenghThreshold--;
			}
		}
	}
};


#endif
