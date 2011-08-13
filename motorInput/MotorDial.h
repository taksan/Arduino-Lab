class MotorDial {
public:
	static const int terminalCount = 3;
	enum Direction {
		none = 0,
		clockwise = 1,
		counterClockwise = 2
	};
	MotorDial(int pin1, int pin2, int pin3) {
		terminals[0] = pin1;
		terminals[1] = pin2;
		terminals[2] = pin3;
		previousPinValue[0] = 0;
		previousPinValue[1] = 0;
		previousPinValue[2] = 0;
	
		previousChangedIndex = 0;
		isClockwise = true;
	}

	Direction turnDirection() {
		for (int i=0; i < terminalCount; i++) {
			if (didTerminalIndexChanged(i)) {
				return getDirection();
			}
		}
		return none;
	}

private:
	Direction getDirection() 
	{
		if (turnedClockwise())
			return clockwise;
		else
			return counterClockwise;
	}
	
	boolean turnedClockwise() 
	{
		if (previousChangedIndex != changedIndex) {
			if (isHigherThan(previousChangedIndex, changedIndex)) {
				isClockwise = false;		
			}
			else {
				isClockwise = true;
			}
		}
		return isClockwise;
	}



	int isHigherThan(int index1, int index2)
	{
		if (index1 == 2 && index2 ==0) 
			return 0;

		if (index1 == 0 && index2 ==2) 
			return 1;

		return index1 > index2;
	}

	boolean didTerminalIndexChanged(int termIndex) {
	  int terminal = terminals[termIndex];
	  boolean changed = false;
	  int value = analogRead(terminal);
	  if ((previousPinValue[termIndex] != value) && (value != 0)) {
		changed = true;
		previousChangedIndex = changedIndex;
		changedIndex = termIndex;
	  }
	  previousPinValue[termIndex] = value;  
	  return changed;
	}

	int terminals[3];
	int previousPinValue[3];
	int changedIndex;
	int previousChangedIndex;
	boolean isClockwise;

};

