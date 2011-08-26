#ifndef __EYE__H___
#define __EYE__H___

#define STRENGH_THRESHOLD 3

class Eye {
public:
	Eye(ArduinoApi * api, int8_t pin):
		api(api),
		pin(pin),
		adjustFactor(1),
		previousIntensity(0)
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
		previousIntensity = getIntensity();
		level = api->_analogRead(pin);
	}

	bool isStronglyInfluenced() {
		return getIntensity() > STRENGH_THRESHOLD;
	}

	bool isWeaklyInfluenced() {
		return !isStronglyInfluenced();
	}

	bool previousIntensityWasStrong() {
		return previousIntensity > STRENGH_THRESHOLD;
	}

	int16_t getIntensity() {
		int16_t levelOffset = level - baseLevel;
		return levelOffset * adjustFactor;
	}

	int16_t getLevel() { 
		return level;
	}

	bool isStrongerThan(Eye * anotherEye) {
		return (this->getIntensity() - STRENGH_THRESHOLD/2) > anotherEye->getIntensity();
	}

private:
	int8_t pin;
	int16_t level;
	int16_t previousIntensity;
	int16_t baseLevel;
	float adjustFactor;

	ArduinoApi * api;
};

#endif
