#ifndef COMMON___H__
#define COMMON___H__

#include <Arduino.h>

#define ABS(X) ((X)<0?-(X):X)
#define MIN(A,B) (((A)<(B))?(A):(B))

#define DIR_0_INIT_THRUST_ANGLE 10
#define DIR_180_INIT_THRUST_ANGLE 170
#define INIT_DIR 5
#define END_DIR  175
#define TIME_TO_DO_180 400
#define STEP_ANGLE 3
#define INTENSITY_FACTOR(X) STEP_ANGLE * ((float)X/127)

enum MoveDirection {
	mdStop,
	mdAhead,
	mdBack,
	mdRight,
	mdLeft
};



#endif
