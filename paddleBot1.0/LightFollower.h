#ifndef LIGHT_FOLLOWER__H_
#define LIGHT_FOLLOWER__H_

#include "AbstractLightFollower.h"
#include "PaperBot.h"

class LightFollower: public AbstractLightFollower {
public:
	LightFollower(PaperBot * bot) : bot(bot){
	}

	bool canChangeDirection() {
		return bot->isStable();
	}
private:
	PaperBot * bot;
};

#endif
