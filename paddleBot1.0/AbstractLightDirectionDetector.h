#ifndef ABSTRACT_LIGHT_DIRECTION_DECTECTOR
#define ABSTRACT_LIGHT_DIRECTION_DECTECTOR

namespace DirectionValue {
	enum Direction {
		dvGoNowhere = 0,
		dvGoAhead,
		dvTurnLeft,
		dvTurnRight
	};
}

using namespace DirectionValue;

class AbstractLightDirectionDetector {
public:

	virtual void update() = 0;
	virtual Direction getDirectionToGo() = 0;
	virtual int getIntensity() = 0;
};


#endif
