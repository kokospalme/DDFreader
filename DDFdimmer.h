/*
 * DDFdimmer.h
 *
 *  Created on: 26 Oct 2022
 *      Author: Chris
 */

#ifndef DDFDIMMER_H_
#define DDFDIMMER_H_

#include <Arduino.h>
#include <DDF_defines.h>


class DDFdimmer{	//range
public:
	bool exist = false;
	bool isMaster = true;
	int dmxchannel = -1;
	int finedmxchannel = -1;
	int type = curve_linear;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	double minval = 0;
	double maxval = 100;
	double value = 0;
private:

};



#endif /* LIBRARIES_DDFDIMMER_H_ */
