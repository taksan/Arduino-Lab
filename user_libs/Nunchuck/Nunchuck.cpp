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

#include "Nunchuck.h"
 
void Nunchuck::begin() 
{
    // init the buffers
	for (int i = 0; i<3; i++) {
    	axis[i][AXIS_MIN] = 90;
		axis[i][AXIS_MAX] = 160;
		axis[i][AXIS_AVERAGE] = 100;
	}

	// init Wire library
    Wire.begin();
            
    // init controller
    delay(1);
    Wire.beginTransmission(NUNCHUCK_DEVICE);	// device address
    Wire.write((uint8_t)0xF0);		                    // 1st initialisation register
    Wire.write((uint8_t)0x55);		                    // 1st initialisation value
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission(NUNCHUCK_DEVICE);
    Wire.write((uint8_t)0xFB);		                    // 2nd initialisation register
    Wire.write((uint8_t)0x00);		                    // 2nd initialisation value
    Wire.endTransmission();
    delay(1);

	calibrateJoy();
}

void Nunchuck::calibrateJoy() {
	zeroJoyX = joyX;
	zeroJoyY = joyY;
}

void Nunchuck::update() {

    int cnt = 0;
	int tmp = 0;
	Wire.requestFrom (NUNCHUCK_DEVICE, 6); // request 6 bytes of data from nunchuck
	while (Wire.available ()) {
		// receive each byte as an integer
		status[cnt] = Wire.read();
		cnt++;
	}
	
	if (cnt > 5) {
		lastZ = buttonZ;
		lastC = buttonC;
		lastJoyX = readJoyX();
		lastJoyY = readJoyY();

		buttonZ = !(status[5] & BUTTONZ_BIT);
		buttonC = !((status[5] & BUTTONC_BIT) >> 1);
		joyX = (status[0]);
		joyY = (status[1]);
		
		for (int i = 0; i < 3; i++) {
			tmp = status[i+2];
            if (tmp > axis[i][AXIS_AVERAGE] + 3 
			|| tmp < axis[i][AXIS_AVERAGE] - 3 ) 
				axis[i][AXIS_AVERAGE] = tmp; 
			
			if (tmp!=0 && tmp < axis[i][AXIS_MIN]) axis[i][AXIS_MIN] = tmp;
			else if (tmp > axis[i][AXIS_MAX]) axis[i][AXIS_MAX] = tmp;
		}

		_send_zero(); // send the request for next bytes
	}
}

// return raw acceleration value 
int Nunchuck::readAccelX() {
	return max(axis[0][AXIS_AVERAGE] - axis[0][AXIS_MIN], 0);
}

// return raw acceleration value 
int Nunchuck::readAccelY() {
	return max(axis[1][AXIS_AVERAGE] - axis[1][AXIS_MIN], 0);
}

// return raw acceleration value 
int Nunchuck::readAccelZ() {
	return max(axis[2][AXIS_AVERAGE] - axis[2][AXIS_MIN], 0);
}

// return acceleration value mapped into a 0 - 180 range
int Nunchuck::readAngleX() {
	return map(axis[0][AXIS_AVERAGE], axis[0][AXIS_MIN], axis[0][AXIS_MAX], 0, 180);
}
// return acceleration value mapped into a 0 - 180 range
int Nunchuck::readAngleY() {
	return map(axis[1][AXIS_AVERAGE], axis[1][AXIS_MIN], axis[1][AXIS_MAX], 0, 180);
}
// return acceleration value mapped into a 0 - 180 range
int Nunchuck::readAngleZ() {
	return map(axis[2][AXIS_AVERAGE], axis[2][AXIS_MIN], axis[2][AXIS_MAX], 0, 180);
}

// return if the button was pressed
boolean Nunchuck::zPressed() {
	return (buttonZ && ! lastZ);
}
// return if the button was pressed
boolean Nunchuck::cPressed() {
	return (buttonC && ! lastC);
}

// return raw button value
boolean Nunchuck::readZ() {
	return buttonZ;
}
// return raw button value
boolean Nunchuck::readC() {
	return buttonC;
}

// for using the joystick like a digital button
boolean Nunchuck::rightJoy(int threshold) {
	return (readJoyX() > threshold and lastJoyX <= threshold);
}

// for using the joystick like a digital button
boolean Nunchuck::leftJoy(int threshold) {
	return (readJoyX() < -threshold and lastJoyX >= -threshold);
}

// for using the joystick like a digital button
boolean Nunchuck::upJoy(int threshold) {
	return (readJoyY() > threshold and lastJoyY <= threshold);
}

// for using the joystick like a digital button
boolean Nunchuck::downJoy(int threshold) {
	return (readJoyY() < -threshold and lastJoyY >= -threshold);
}

// for using the joystick like an analog button
int Nunchuck::readJoyX() {
	return (int) joyX - zeroJoyX;
}

// for using the joystick like an analog button
int Nunchuck::readJoyY() {
	return (int)joyY - zeroJoyY;
}

// send zeros to request next 6 bytes
void Nunchuck::_send_zero()
{
    int i;
    for (i=0; i<3; i++) {								// Send 0x00 3 times
    	Wire.beginTransmission (NUNCHUCK_DEVICE);      	// transmit to nunchuck device 
	    Wire.write ((uint8_t)0x00);           					// sends one byte
	    Wire.endTransmission ();    					// stop transmitting
	}
}

