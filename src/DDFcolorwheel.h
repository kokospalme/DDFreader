/*
 * DDFcolorwheel.h
 *
 *  Created on: 06 Jan 2023
 *      Author: Chris
 */

#ifndef DDFCOLORWHEEL_H_
#define DDFCOLORWHEEL_H_
#include <Arduino.h>
#include <DDF_defines.h>

class DDFcolorwheel{
public:

	virtual ~DDFcolorwheel(){
		// delete[] _singlecolorArray;
		// delete[] _colorwheelArray;
	}

	void set(colorwheel_t info){	//set info
		_info = info;	//update info
	}

	colorwheel_t get(){	//return info
		return _info;
	}

	void setColors(singlecolor_t* colorArray){	//set colors in color array
		_singlecolorArray = colorArray;
	}

	singlecolor_t getCcolor(uint16_t colorNo){	//get a single color
		if(colorNo < sizeof(_singlecolorArray)-1){
			return _singlecolorArray[colorNo];
		}else{
			singlecolor_t empty;
			return empty;
		}
	}

private:
	singlecolor_t* _singlecolorArray;
	colorwheel_t _info;
};

#endif /* DDFCOLORWHEEL_H_ */
