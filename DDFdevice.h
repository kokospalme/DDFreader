/*
 * DDFdevice.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef DDFDEVICE_H_
#define DDFDEVICE_H_
#include "DDFreader.h"
#include "AbstractDDFfunction.h"

#include "DDFcolorwheel.h"

#include "DDFdimmers.h"	//dimmers, rgbs, steps... objects
#include "DDFrgbs.h"
#include "DDFpositions.h"
#include "DDFsteps.h"
#include "DDFfocusses.h"
#include "DDFfrosts.h"
#include "DDFgobowheels.h"
#include "DDFcolorwheels.h"
#include "DDFmatrices.h"
#include "DDFprisms.h"
#include "DDFptspeeds.h"
#include "DDFraws.h"
#include "DDFshutters.h"	//ToDo: implement im Detail (shutter funktionen etc.)
#include "DDFzooms.h"


class DDFdevice{
public:
	DDFdevice(ddfInformation_t ddfInfo, deviceInformation_t deviceInfo);
	
	void addColorwheels(DDFcolorwheel* array);

	void addDimmer(DDFdimmer dimmer, uint16_t no);
	void setDimmer(uint16_t dimmerNo, double value);
	void setDimmer(double value);

	void addRgb(DDFrgb rgb, uint16_t no);
	void addStep(singlestep_t step, uint16_t stepfuncNo, uint16_t stepNo);
	void addPosition(DDFposition position, uint16_t no);
	void addFocus(DDFfocus focus, uint16_t no);
//	void addRaw(DDFraw raw, uint16_t no);

	void print();
private:
	ddfInformation_t _ddfInfo;	//info about ddf header
	deviceInformation_t _deviceInfo;	//info about device 

	uint16_t _functionCount = 1;	//max amount of functions

	uint16_t _colorwheelCount = 0;
	uint16_t _singlecolorCount = 0;
	uint16_t _dimmerCount = 0;	//max amount of dimmers
	uint16_t _focusCount = 0;	//max amount of focusses
	uint16_t _frostCount = 0;
	uint16_t _gobowheelCount = 0;
	uint16_t _singlegoboCount = 0;
	uint16_t _matrixCount = 0;
	uint16_t _positionCount = 0;	//max amount of positions
	uint16_t _prismCount = 0;
	uint16_t _ptspeedCount = 0;
	uint16_t _rawCount = 0;
	uint16_t _rgbCount = 0;	//max amount of rgbs
	uint16_t _shutterCount = 0;
	uint16_t _stepfuncCount = 0;	//max amount of stepfunctions
	uint16_t _singlestepCount = 0;	//max amount of singlesteps
	uint16_t _zoomCount = 0;

	uint16_t _colowheelCounter = 0;
	uint16_t _dimmerCounter = 0;	//max amount of dimmers
	uint16_t _focusCounter = 0;	//max amount of focusses
	uint16_t _frostCounter = 0;
	uint16_t _gobowheelCounter = 0;
	uint16_t _matrixCounter = 0;
	uint16_t _positionCounter = 0;	//max amount of positions
	uint16_t _prismCounter = 0;
	uint16_t _ptspeedCounter = 0;
	uint16_t _rawCounter = 0;
	uint16_t _rgbCounter = 0;	//max amount of rgbs
	uint16_t _shutterCounter = 0;
	uint16_t _stepCounter = 0;	//max amount of steps
	uint16_t _zoomCounter = 0;


	AbstractDDFfunction* fnc_array;

	DDFcolorwheel* _colorwheels;
	DDFdimmers* _dimmers;	//ToDo: functions: raw, matrix, colorwheel, gobowheel, frost, ptspeed,prism, zoom, shutter
	DDFshutters* _shutters;
	DDFrgbs* _rgbs;
	DDFpositions* _positions;
	DDFptspeeds* _ptspeeds;
	DDFprisms* _prisms;
	DDFzooms* _zooms;
	DDFsteps* _steps;
	DDFfocusses* _focusses;
	DDFraws* _raws;
	DDFgobowheels* _gobowheels;
	DDFfrosts* _frosts;
	DDFmatrices* _matrices;

	bool virtualDimmer = true;	//true if dimmer virtual
	double virtualDimmerValue = 0;

	uint8_t* dmxOutput;

};



#endif /* LIBRARIES_DDFREADER_DDFDEVICE_H_ */
