#ifndef PAPER_BOT_MOVE_H__
#define PAPER_BOT_MOVE_H__

#include "Common.h"

class PaperBot;

class PaperBotMove {
	public:
		virtual void perform()=0;
		virtual void setup()=0;
		virtual void stop();
};

class NoMovement: public PaperBotMove {
	public:
		void perform() {}

		void setup() {}

		void stop() {}
};

class StepAhead: public PaperBotMove
{	
public:
	StepAhead(PaperBot * aBot):bot(aBot) { }

	void perform();
		
	void setup(); 

	void stop();
private:
	PaperBot * bot;
};

class StepBack: public PaperBotMove
{	
public:
	StepBack(PaperBot * aBot):bot(aBot) { }

	void perform();
		
	void setup(); 

	void stop();
private:
	PaperBot * bot;
};


class TurnMove: public PaperBotMove {
	public:
		TurnMove(PaperBot * bot, int angleToReinit, int directionToStartMoving, int thrustToStartMoving, int angleIncrement) {
			this->bot = bot;
			this->angleToReinit          = angleToReinit;
			this->directionToStartMoving = directionToStartMoving;
			this->thrustToStartMoving    = thrustToStartMoving;
			this->angleIncrement         = angleIncrement;
		}

		virtual void perform();
		
		virtual void setup(); 

	protected:
		virtual boolean isTheEndAngle(int angle) {
			return false;
		}
	protected:	
		PaperBot *bot;
	private:	
		int angleToReinit;
		int	directionToStartMoving;
		int	thrustToStartMoving;
		int angleIncrement;
};

class TurnRightWhenFacingAhead : public TurnMove {
	public:
		TurnRightWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, END_DIR, 110, -5) { }

		void stop();
	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
};

class TurnRightWhenFacingBack : public TurnMove {
	public:
		TurnRightWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, END_DIR, 70, -5) { }
		void stop();

	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
};

class TurnLeftWhenFacingAhead : public TurnMove {
	public:
		TurnLeftWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, INIT_DIR, 70, 5) { }

		void stop();

	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle >= END_DIR;
		}
};

class TurnLeftWhenFacingBack : public TurnMove {
	public:
		TurnLeftWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, INIT_DIR, 110, 5) { }

		void stop();

	protected:
		boolean isTheEndAngle(int angle)   { 
			return angle >= END_DIR;
		}
};

#endif
