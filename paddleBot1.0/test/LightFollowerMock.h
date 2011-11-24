#ifndef LIGHT_FOLLOWER_MOCK__H__
#define LIGHT_FOLLOWER_MOCK__H__

#include "../AbstractLightFollower.h"

class LightFollowerMock : public AbstractLightFollower {
public:
	LightFollowerMock():isAbleToChangeDirection(true){}

	virtual bool canChangeDirection() {
		return isAbleToChangeDirection;
	}

	void setCantChangeDirection() {
		isAbleToChangeDirection = false;
	}

	void setCanChangeDirection() {
		isAbleToChangeDirection = true;
	}

private:
	bool isAbleToChangeDirection;

};

#endif
