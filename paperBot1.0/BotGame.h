#ifndef BOT_GAME__H_
#define BOT_GAME__H_

class BotGame {
public:
	virtual void tick() = 0;
	BotGame():nextReadyTime(0){}

protected:
	bool isReady() {
		return millis() > nextReadyTime;
	}

	void setTimeToWaitUntilNextReady(int32_t timeToWait) {
		nextReadyTime = millis() + timeToWait;
	}

private:
	int32_t nextReadyTime;
};

#endif

