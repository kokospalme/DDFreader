/*
 * DDFstrobe.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef DDFSTROBE_H_
#define DDFSTROBE_H_

#include <Arduino.h>
#include <DDF_defines.h>

struct strobe_t{	//strobe channel
	int dmxchannel = -1;
	bool exist = false;
	bool isVirtual = true;

	bool linear_exist = false;	//linear curve
	int linear_mindmx = -1;
	int linear_maxdmx = -1;
	double linear_minval = -1;
	double linear_maxval = -1;

	bool pulse_exist = false;	//pulse curve
	int pulse_mindmx = -1;	
	int pulse_maxdmx = -1;
	double pulse_minval = -1;
	double pulse_maxval = -1;

	bool random_exist = false;	//random curve
	int random_mindmx = -1;	
	int random_maxdmx = -1;
	double random_minval = -1;
	double random_maxval = -1;

};

enum strobeCurves{
	strobe_linear,
	strobe_pulse,
	strobe_random
};


class DDFstrobe{	//strobe class
friend class DDFreader;
public:
	virtual ~DDFstrobe(){	//deconstructor
		// delete[] _singlecolorArray;
		// delete[] _colorwheelArray;
	}
	strobe_t get(){	//return info
		return _info;
	}

private:
	void set(strobe_t info){	//set info
		_info = info;	//update info
	}

	strobe_t _info;

};


#endif /* DDFSTROBE_H_ */
