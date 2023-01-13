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

struct singlecolor_t{	//struct for details about a single color of a colorwheel
	uint16_t wheelNo = 0;
	uint32_t color = 0xFFFFFF;
	uint8_t colorR = 0xFF;
	uint8_t colorG = 0xFF;
	uint8_t colorB = 0xFF;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
};

struct colorwheel_t{	//struct for details about a single colorwheel
	uint16_t size = 0;
	uint16_t wheelNo = 0;
	int dmxchannel = -1;	//dmx channel

	int rainbow_stopMindmx = -1;	//rainbow/wheelrotation STOP
	int rainbow_stopMaxdmx = -1;
	double rainbow_stopMinvalue = -1;
	double rainbow_stopMaxvalue = -1;

	int rainbow_cwMindmx = -1;	//rainbow/wheelrotation CW
	int rainbow_cwMaxdmx = -1;
	double rainbow_cwMinvalue = -1;
	double rainbow_cwMaxvalue = -1;

	int rainbow_ccwMindmx = -1;	//rainbow/wheelrotation CCW
	int rainbow_ccwMaxdmx = -1;
	double rainbow_ccwMinvalue = -1;
	double rainbow_ccwMaxvalue = -1;

	int random_fastMindmx = -1;	//random color
	int random_fastMaxdmx = -1;

	int random_mediumMindmx = -1;
	int random_mediumMaxdmx = -1;

	int random_slowMindmx = -1;
	int random_slowMaxdmx = -1;
};

class DDFcolorwheel{
	friend class DDFreader;
public:
	virtual ~DDFcolorwheel(){	//deconstructor
		// delete[] _singlecolorArray;
		// delete[] _colorwheelArray;
	}
	colorwheel_t get(){	//return info
		return _info;
	}

	singlecolor_t getColor(uint16_t colorNo){	//get a single color
		if(colorNo < sizeof(_singlecolorArray)-1){
			return _singlecolorArray[colorNo];
		}else{
			singlecolor_t empty;
			return empty;
		}
	}

private:

	void set(colorwheel_t info){	//set info
		_info = info;	//update info
	}

	void setColors(singlecolor_t* colorArray){	//set colors in color array
		_singlecolorArray = colorArray;
	}

	singlecolor_t* _singlecolorArray;
	colorwheel_t _info;
};

#endif /* DDFCOLORWHEEL_H_ */
