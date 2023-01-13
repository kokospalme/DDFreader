/*
 * DDFzoom.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFZOOM_H_
#define LIBRARIES_DDFREADER_DDFZOOM_H_
#include <Arduino.h>
#include <DDF_defines.h>


class DDFzoom{	//range
public:
	bool exist = false;
	int dmxchannel = -1;
	int finedmxchannel = -1;
	int type = curve_linear;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	double minval = 0;
	double maxval = 100;
private:

};




#endif /* LIBRARIES_DDFREADER_DDFZOOM_H_ */
