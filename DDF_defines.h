/*
 * DDFdefines.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDF_DEFINES_H_
#define LIBRARIES_DDFREADER_DDF_DEFINES_H_
#include <Arduino.h>
#include "DDFrgb.h"

enum functiontypeId{
	dimmer,
	focus,
	position,
	rgb
};

enum dimCurves{
	curve_linear
};

enum steptypes{
	steps_color,
	steps_gobo,
	steps_open
};

enum matrixtype{
	matrix_cartesian,
	matri_polar
};


struct singlestep_t{	//step type
	uint8_t steptype = 0;
	uint32_t val = 0;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
	uint16_t stepfuncNo = 0;
};

struct stepfunc_t{
	int dmxchannel = -1;
	uint16_t currentStep = 0;
	uint16_t stepCount = 1;	// min. 1 singlestep/ function
	uint16_t size = 1;
};

struct singlecolor_t{
	uint16_t color = 0xFFFF;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
};

struct colorwheel_t{
	int dmxchannel = -1;
	uint16_t currentColor = 0;
//	uint16_t colorCount = 1;	// min. 1 gobo/wheel ToDo: obsolet?
	uint16_t size = 1;
};

struct singlegobo_t{
	String path = "empty.gif";
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
	int gobowheelNo = -1;
};

struct gobowheel_t{
	int dmxchannel = -1;
	uint16_t currentGobo = 0;
//	uint16_t goboCount = 1;	// min. 1 gobo/wheel ToDo: obsolet?
	uint16_t size = 1;
};

struct matrixPixel_t{
	int x_angle = -1;	//-1 = not set
	int x_distance = -1;
	DDFrgb pixel;
};

#endif /* LIBRARIES_DDFREADER_DDF_DEFINES_H_ */
