#include "../PaperBot.h"
#include "../PaperBotMove.h"

class PaperBotMock : public PaperBot {
public:
	PaperBotMock(int a, int b):PaperBot(a,b){}
	virtual void setDirectionAndWait(int16_t angle) {
		PaperBot::setDirectionAndWait(angle);
		printf("DIR: %d\n", angle);
	}

	void setThrustAndWait(int16_t angle) {
		PaperBot::setThrustAndWait(angle);
		printf("THRUST: %d\n", angle);
	}
};


int main()
{
	PaperBot * p = new PaperBotMock(1,2);
	TurnMove * move = new TurnRightWhenFacingBack(p);
//	StepBack * move = new StepBack(p);

	for (int i=0; i < 30; i++)
		move->perform(127);
}
