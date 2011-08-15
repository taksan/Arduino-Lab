#ifndef PAPER_BOT_MOVE_H__
#define PAPER_BOT_MOVE_H__

#include "Common.h"
#define STEP_ANGLE 5

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

class StepAction: public PaperBotMove
{
public:
	StepAction(PaperBot * aBot, int aDirToStartMovingFromFront, int aDirToStartMovingFromBack):
		bot(aBot),
		dirToStartMovingFromFront(aDirToStartMovingFromFront),
		dirToStartMovingFromBack(aDirToStartMovingFromBack),
		thrustStep(STEP_ANGLE),
		direction(1)
		{ }

	void perform();
		
	void setup();

	void stop(){};

	static const int initialThrustForStartFromFront = 40;
	static const int initialThrustForStartFromBack  = 140;

private:
	int getThrustStep(); 
	void updateStepDirection();

	PaperBot * bot;
	int dirToStartMovingFromFront;
	int dirToStartMovingFromBack;
	int thrustStep;
	int direction;

};

class StepAhead: public StepAction
{	
public:
	StepAhead(PaperBot * aBot):
		StepAction(aBot, 
				   StepAction::initialThrustForStartFromFront, 
				   StepAction::initialThrustForStartFromBack) 
   { }
};

class StepBack: public StepAction
{	
public:
	StepBack(PaperBot * aBot):
		StepAction(aBot, 
				   StepAction::initialThrustForStartFromBack,
				   StepAction::initialThrustForStartFromFront) 
   { }
};


class TurnMove: public PaperBotMove {
	public:
		TurnMove(PaperBot * bot, int angleToReinit, int directionToStartMoving, int thrustToStartMoving, int angleIncrement):
			bot(bot),
			angleToReinit(angleToReinit),
			directionToStartMoving(directionToStartMoving),
			thrustToStartMoving(thrustToStartMoving),
			angleIncrement(angleIncrement)
		{ }

		virtual void perform();
		
		virtual void setup(); 

	protected:
		virtual boolean isPastTheFinalAngle(int angle) {
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
		TurnRightWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, END_DIR, 110, -STEP_ANGLE) { }

		void stop();
	protected:
		boolean isPastTheFinalAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
};

class TurnRightWhenFacingBack : public TurnMove {
	public:
		TurnRightWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, END_DIR, 70, -STEP_ANGLE) { }
		void stop();

	protected:
		boolean isPastTheFinalAngle(int angle)   { 
			return angle <= INIT_DIR;
		}
};

class TurnLeftWhenFacingAhead : public TurnMove {
	public:
		TurnLeftWhenFacingAhead(PaperBot * bot):TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, INIT_DIR, 70, STEP_ANGLE) { }

		void stop();

	protected:
		boolean isPastTheFinalAngle(int angle)   { 
			return angle >= END_DIR;
		}
};

class TurnLeftWhenFacingBack : public TurnMove {
	public:
		TurnLeftWhenFacingBack(PaperBot * bot):TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, INIT_DIR, 110, STEP_ANGLE) { }

		void stop();

	protected:
		boolean isPastTheFinalAngle(int angle)   { 
			return angle >= END_DIR;
		}
};

#endif
