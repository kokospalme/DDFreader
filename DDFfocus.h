/*
 * DDFdimmer.h
 *
 *  Created on: 26 Oct 2022
 *      Author: Chris
 */

#ifndef DDFFOCUS_H_
#define DDFFOCUS_H_
#include <Arduino.h>
#include <DDF_defines.h>

class DDFfocus{
public:
	int dmxchannel = -1;
	uint8_t type = curve_linear;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	double minval = 0;
	double maxval = 100;
private:

};



#endif /* LIBRARIES_DDFDIMMER_H_ */
