/*
 * Nunchuck library - Tiago Barros (2011)
 * The code was changed to get a smooth reading from x, y and z axis.
 * Also included a better initialization to work with other versions of
 * hardware.
 * 
 * This file is an adaptation of the code by these authors:
 *
 * WiiChuck -- Use a Wii Nunchuck
 * Tim Hirzel http://www.growdown.com
 *
 * Tod E. Kurt, http://todbot.com/blog/
 *
 * The Wii Nunchuck reading code is taken from Windmeadow Labs
 * http://www.windmeadow.com/node/42
 */

#ifndef Nunchuck_h
#define Nunchuck_h

#include "Arduino.h" 
#include "../Wire/Wire.h"
#include <math.h>

#define NUNCHUCK_DEVICE     0x52
#define BUTTONZ_BIT         B00000001
#define BUTTONC_BIT         B00000010

#define JOYSTICK_THRESHOLD  60
#define AXIS_MIN            0
#define AXIS_MAX            1
#define AXIS_AVERAGE        2
#define AXIS_BUFFER_SIZE    3


class Nunchuck {
    public:
	    // init functions
	    void begin();
        void calibrateJoy();
        void update();

		// accel functions
        int readAccelX();
        int readAccelY();
        int readAccelZ();
		
		// angle functions
        int readAngleX();
        int readAngleY();
        int readAngleZ();

		// buttons functions
        boolean zPressed();
        boolean cPressed();
        boolean readZ();
        boolean readC();

		// Joystick functions
        // for using the joystick like a digital button
        boolean rightJoy(int threshold=JOYSTICK_THRESHOLD);
        boolean leftJoy(int threshold=JOYSTICK_THRESHOLD);
        boolean upJoy(int threshold=JOYSTICK_THRESHOLD);
        boolean downJoy(int threshold=JOYSTICK_THRESHOLD);
        // for using the joystick like an analog button
        int readJoyX();
        int readJoyY();

    private:
        byte joyX;
        byte joyY;
        boolean buttonZ;
        boolean buttonC;
        boolean lastZ, lastC;

        uint8_t status[6];              // array to store nunchuck output
        uint8_t zeroJoyX;               
        uint8_t zeroJoyY;               
        int lastJoyX;
        int lastJoyY;
	public:
        int axis[3][AXIS_BUFFER_SIZE]; 	// for each axis, store the minimum, maximum and average
										// to calculate relative value for servo angles
		
        void _send_zero();
};


#endif
