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

struct dimmer_t{
	bool exist = false;
	bool isMaster = false;

	int dmxchannel = -1;
	int finedmxchannel = -1;

	int type = curve_linear;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;

	double minval = 0;
	double maxval = 100;
};

class DDFdimmer{	//dimmer class
friend class DDFreader;
public:
	virtual ~DDFdimmer(){	//deconstructor
		// delete[] _singlecolorArray;
		// delete[] _colorwheelArray;
	}
	dimmer_t get(){	//return info
		return _info;
	}
private:
	void set(dimmer_t info){	//set info
		_info = info;	//update info
	}

	dimmer_t _info;
};



#endif /* DDFDIMMER_H_ */
