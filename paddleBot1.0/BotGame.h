#ifndef BOT_GAME__H_
#define BOT_GAME__H_

class BotGame {
public:
	virtual void doTick() = 0;
	BotGame():nextReadyTime(0){}

	void tick()
	{
		if (!isReady())
			return;
		doTick();
	}

protected:
	bool isReady() {
		return millis() > nextReadyTime;
	}

	void setWaitProportionalToGivenIntensity(int16_t intensity) {
		int16_t timeToWait = (127-ABS(intensity))*2;
		if (timeToWait < 20) {
			timeToWait = 20;
		}
		setTimeToWaitUntilNextReady(timeToWait);
	}

private:
	uint32_t nextReadyTime;

	void setTimeToWaitUntilNextReady(int32_t timeToWait) {
		nextReadyTime = millis() + timeToWait;
	}
};

#endif

