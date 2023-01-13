/*
 * DDFshutter.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef DDFSHUTTER_H_
#define DDFSHUTTER_H_

#include <Arduino.h>
#include <DDF_defines.h>


struct shutterstep_t{
	uint8_t type = SHUTTERTYPE_OPEN;
	int mindmx = -1;
	int maxdmx = -1;
};

struct shutter_t{
	bool exist = false;
	bool isVirtual = false;
	int dmxchannel = -1;
	int finedmxchannel = -1;
}

class DDFshutter{	//range
friend class DDFreader;
public:
	virtual ~DDFshutter(){	//deconstructor
		// delete[] _singlecolorArray;
		// delete[] _colorwheelArray;
	}
	shutter_t get(){	//return info
		return _info;
	}

	shutter_t getStep(uint16_t stepNo){	//get a single step
		if(colorNo < sizeof(_singlecolorArray)-1){
			return _singlecolorArray[colorNo];
		}else{
			shutter_t empty;
			return empty;
		}
	}
private:

	void set(colorwheel_t info){	//set info
		_info = info;	//update info
	}

	void setSteps(shutterstep_t* shutterstepArray){	//set colors in color array
		_shutterstepArray = shutterstepArray;
	}

	shutterstep_t* _shutterstepArray;
	shutter_t _info;

};


#endif /* LIBRARIES_DDFREADER_DDFSHUTTER_H_ */
