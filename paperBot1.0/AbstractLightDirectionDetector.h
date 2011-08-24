#ifndef ABSTRACT_LIGHT_DIRECTION_DECTECTOR
#define ABSTRACT_LIGHT_DIRECTION_DECTECTOR

namespace DirectionValue {
	enum Direction {
		dvGoAhead = 0,
		dvTurnLeft,
		dvTurnRight
	};
}

using namespace DirectionValue;

class AbstractLightDirectionDetector {
public:

	virtual void update() = 0;
	virtual Direction getDirectionToGo() = 0;
};


#endif
