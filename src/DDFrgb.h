/*
 * DDFdimmer.h
 *
 *  Created on: 26 Oct 2022
 *      Author: Chris
 */

#ifndef DDFRGB_H_
#define DDFRGB_H_
#include <Arduino.h>
#include "DDF_defines.h"


class DDFrgb{
public:
	bool exist = false;
	int redDmxchannel = -1;
	int redFinedmxchannel = -1;
	int greenDmxchannel = -1;
	int greenFinedmxchannel = -1;
	int blueDmxchannel = -1;
	int blueFinedmxchannel = -1;
	int whiteDmxchannel = -1;
	int whiteFinedmxchannel = -1;
	int amberDmxchannel = -1;
	int amberFinedmxchannel = -1;
	int uvDmxchannel = -1;
	int uvFinedmxchannel = -1;
private:

};



#endif /* LIBRARIES_DDFDIMMER_H_ */
