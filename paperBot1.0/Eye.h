#ifndef __EYE__H___
#define __EYE__H___

#define STRENGH_THRESHOLD 3

class Eye {
public:
	Eye(ArduinoApi * api, int16_t pin):
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

	void setAdjustFactorAgainst(int otherLevel)
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

	int getIntensity() {
		int levelOffset = level - baseLevel;
		return levelOffset * adjustFactor;
	}

	int getLevel() { 
		return level;
	}

	bool isStrongerThan(Eye * anotherEye) {
		return (this->getIntensity() - STRENGH_THRESHOLD/2) > anotherEye->getIntensity();
	}

private:
	int16_t pin;
	int level;
	int previousIntensity;
	int baseLevel;
	float adjustFactor;

	ArduinoApi * api;
};

#endif
