#ifndef PAPER_BOT_MOVE_H__
#define PAPER_BOT_MOVE_H__

#include "Common.h"
#define STEP_ANGLE 3
#define INTENSITY_FACTOR(X) STEP_ANGLE * ((float)X/64)

#define ANGLE_TO_MOVE_TURNING_FROM_FRONT 80
#define ANGLE_TO_MOVE_TURNING_FROM_BACK  100

class PaperBot;

class PaperBotMove {
	public:
		virtual void perform(int16_t intensity){}
		virtual void setup(){}
		virtual bool isStable() { return true; }
		virtual void stop(){}
};

class NoMovement: public PaperBotMove {
	public:
		void perform(int16_t intensity) {}

		void setup() {}

		void stop() {}
};

class StepAction: public PaperBotMove
{
	public:
		StepAction(PaperBot * aBot, int16_t aDirToStartMovingFromFront, int16_t aDirToStartMovingFromBack):
			bot(aBot),
			dirToStartMovingFromFront(aDirToStartMovingFromFront),
			dirToStartMovingFromBack(aDirToStartMovingFromBack),
			thrustStep(STEP_ANGLE),
			direction(1),
			stable(false)
	{ }

		void perform(int16_t intensity);

		void setup();

		void stop(){};

		bool isStable() { return stable; }


	private:
		int16_t getThrustStep(); 
		void updateStepDirection();

		PaperBot * bot;
		int16_t dirToStartMovingFromFront;
		int16_t dirToStartMovingFromBack;
		int16_t thrustStep;
		int16_t direction;
		bool stable;

		static const int16_t initialThrustForStartFromFront = 40;
		static const int16_t initialThrustForStartFromBack  = 140;
		static const int16_t frontThrustTurningPoint = 25;
		static const int16_t backThrustTurningPoint = 155;
};

class StepAhead: public StepAction
{	
	public:
		StepAhead(PaperBot * aBot):
			StepAction(aBot, 
					INIT_DIR,
					END_DIR)
	{ }

};

class StepBack: public StepAction
{	
	public:
		StepBack(PaperBot * aBot):
			StepAction(aBot, 
					END_DIR,
					INIT_DIR)
	{ }
};


class TurnMove: public PaperBotMove {
	public:
		TurnMove(PaperBot * bot, 
		   		 int16_t angleToReinit, 
				 int16_t directionToStartMoving, 
				 int16_t thrustToStartMoving, 
				 int8_t angleIncrement):
			bot(bot),
			angleToReinit(angleToReinit),
			directionToStartMoving(directionToStartMoving),
			thrustToStartMoving(thrustToStartMoving),
			angleIncrement(angleIncrement)
	{ }

		virtual void perform(int16_t intensity);

		virtual void setup(); 

	protected:
		virtual boolean isPastTheFinalAngle(int16_t angle) {
			return false;
		}
	protected:	
		PaperBot *bot;
	private:	
		int16_t angleToReinit;
		int16_t	directionToStartMoving;
		int16_t	thrustToStartMoving;
		int16_t angleIncrement;
};

class TurnRightWhenFacingAhead : public TurnMove {
	public:
		TurnRightWhenFacingAhead(PaperBot * bot):
			TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, INIT_DIR, ANGLE_TO_MOVE_TURNING_FROM_BACK, STEP_ANGLE) { }

		void stop();
	protected:
		boolean isPastTheFinalAngle(int16_t angle)   { 
			return angle >= END_DIR;
		}
};

class TurnRightWhenFacingBack : public TurnMove {
	public:
		TurnRightWhenFacingBack(PaperBot * bot):
			TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, END_DIR, ANGLE_TO_MOVE_TURNING_FROM_FRONT, -STEP_ANGLE) { }

		void stop();

	protected:
		boolean isPastTheFinalAngle(int16_t angle)   { 
			return angle <= INIT_DIR;
		}
};

class TurnLeftWhenFacingAhead : public TurnMove {
	public:
		TurnLeftWhenFacingAhead(PaperBot * bot):
			TurnMove(bot, DIR_0_INIT_THRUST_ANGLE, INIT_DIR, ANGLE_TO_MOVE_TURNING_FROM_FRONT, STEP_ANGLE) { }

		void stop();

	protected:
		boolean isPastTheFinalAngle(int16_t angle)   { 
			return angle >= END_DIR;
		}
};

class TurnLeftWhenFacingBack : public TurnMove {
	public:
		TurnLeftWhenFacingBack(PaperBot * bot):
			TurnMove(bot, DIR_180_INIT_THRUST_ANGLE, INIT_DIR, ANGLE_TO_MOVE_TURNING_FROM_BACK, STEP_ANGLE) { }

		void stop();

	protected:
		boolean isPastTheFinalAngle(int16_t angle)   { 
			return angle >= END_DIR;
		}
};

#endif
