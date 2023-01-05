/*
 * DDFposition.h
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFPOSITION_H_
#define LIBRARIES_DDFREADER_DDFPOSITION_H_
#include <Arduino.h>
#include <DDF_defines.h>


class DDFposition{
public:
	bool exist = false;
	// pan —
	int pan_dmxchannel = -1;
	int pan_finedmxchannel = -1;
	uint8_t pan_mindmx = 0;
	uint8_t pan_maxdmx = 255;
	double pan_range = 540;
	double pan_minval = -270;
	double pan_maxval = 270;
	// tilt |
	int tilt_dmxchannel = -1;
	int tilt_finedmxchannel = -1;
	int tilt_mindmx = 0;
	uint8_t tilt_maxdmx = 255;
	double tilt_range = 270;
	double tilt_minval = -135;
	double tilt_maxval = 135;
private:

};




#endif /* LIBRARIES_DDFREADER_DDFPOSITION_H_ */
