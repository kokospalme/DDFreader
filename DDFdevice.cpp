/*
 * DDFdevice.cpp
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */


#include "DDFdevice.h"

DDFdevice::DDFdevice(String model, String vendor, String author,
		uint16_t colorwheelCount, uint16_t colorCount, uint16_t dimmerCount,uint16_t focusCount, uint16_t frostCount, uint16_t gobowheelCount,
		uint16_t goboCount, uint16_t matrixCount, uint16_t positionCount, uint16_t prismCount,uint16_t ptspeedCount, uint16_t rawCount,
		uint16_t rgbCount, uint16_t shutterCount, uint16_t stepCount, uint16_t stepSinglestepCount, uint16_t zoomCount ){
	_model = model;
	_vendor = vendor;
	_author = author;


	_colorwheelCount = colorwheelCount;
	_singlecolorCount = colorCount;
	_dimmerCount = dimmerCount;	//number of dimmers in this ddf
	_focusCount = focusCount;
	_frostCount = frostCount;
	_gobowheelCount = gobowheelCount;
	_singlegoboCount = goboCount;
	_matrixCount = matrixCount;
	_positionCount = positionCount;
	_prismCount = prismCount;
	_ptspeedCount = ptspeedCount;
	_rawCount = rawCount;
	_rgbCount = rgbCount;
	_shutterCount = shutterCount;
	_stepfuncCount = stepCount;
	_singlestepCount = stepSinglestepCount;
	_zoomCount = zoomCount;


	_functionCount = _dimmerCount + _focusCount + _frostCount + _gobowheelCount + _matrixCount + _positionCount + _prismCount + _ptspeedCount + _rawCount + _rgbCount + _shutterCount + _stepfuncCount + _zoomCount;
	fnc_array = new AbstractDDFfunction[_functionCount];

	colorwheel_t _colorwheelArray[_colorwheelCount];	//temp array
	singlecolor_t _colorArray[_singlecolorCount];
	DDFdimmer _dimmerArray[_dimmerCount];
	DDFfocus _focusArray[_focusCount];
	DDFfrost _frostArray[_frostCount];
	gobowheel_t _gobowheelArray[_gobowheelCount];
	singlegobo_t _goboArray[_singlegoboCount];
	DDFmatrix _matrixArray[_matrixCount];
	DDFposition _positionArray[_positionCount];
	DDFprism _prismArray[_prismCount];
	DDFptspeed _ptspeedArray[_ptspeedCount];
	DDFraw _rawArray[_rawCount];
	DDFrgb _rgbArray[_rgbCount];
	DDFshutter _shutterArray[_shutterCount];
	stepfunc_t _stepfuncArray[_stepfuncCount];
	singlestep_t _stepArray[_singlestepCount];
	DDFzoom _zoomArray[_zoomCount];


	_colorwheels = new DDFcolorwheels(_colorArray, _singlecolorCount, _colorwheelArray, _colorwheelCount);
	_dimmers = new DDFdimmers(_dimmerArray, _dimmerCount);
	_focusses = new DDFfocusses(_focusArray, _focusCount);
	_frosts = new DDFfrosts(_frostArray, _focusCount);
	_gobowheels = new DDFgobowheels(_goboArray, _singlegoboCount,_gobowheelArray, _gobowheelCount);
	_matrices = new DDFmatrices(_matrixArray, _matrixCount);
	_positions = new DDFpositions(_positionArray,_positionCount );
	_prisms = new DDFprisms(_prismArray, _prismCount);
	_ptspeeds = new DDFptspeeds(_ptspeedArray, _ptspeedCount);
	_raws = new DDFraws(_rawArray, _rawCount);
	_rgbs = new DDFrgbs(_rgbArray, _rgbCount);
	_shutters = new DDFshutters(_shutterArray, _shutterCount);
	_steps = new DDFsteps(_stepArray,_singlestepCount, _stepfuncArray, _stepfuncCount);
	_zooms = new DDFzooms(_zoomArray, _zoomCount);

}



void DDFdevice::addDimmer(DDFdimmer dimmer, uint16_t no){

	if(_dimmerCounter < _dimmerCount){
		_dimmers->setDimmer(dimmer, no);
	}else{
		Serial.println("can't add dimmer (array is full)");
		return;
	}

}

void DDFdevice::setDimmer(uint16_t dimmerNo, double value){
	_dimmers->setVal(dimmerNo, value);
}

void DDFdevice::setDimmer(double value){
	if(virtualDimmer){

	}else{
		_dimmers->setVal(0, value);
	}

}

void DDFdevice::addRgb(DDFrgb rgb, uint16_t no){

	if(_rgbCounter < _rgbCount){
		_rgbs->setRgb(rgb, no);
	}else{
		Serial.println("can't add rgb (array is full)");
		return;
	}

}

void DDFdevice::addStep(singlestep_t step, uint16_t stepfuncNo, uint16_t stepNo){
	if(stepfuncNo < _stepfuncCount && stepNo < _steps->getSizeFunc(stepfuncNo)){
		uint16_t _no = 0;
		for(int i = 0; i < stepfuncNo; i++){
			_no += _steps->getSizeFunc(stepfuncNo);
		}
		_no += stepNo;
		if(_no < _steps->getSizeFunc(stepfuncNo)){
			_steps->setStep(step,stepfuncNo, stepNo);
		}
	}
}

void DDFdevice::print(){
	Serial.printf("** DDF device (%s [%s]) **\n", _model.c_str(), _vendor.c_str());
	for(int i = 0; i < _rgbCount; i++){
		DDFdimmer _dim = _dimmers->getDimmer(i);
		Serial.printf("** Dimmer%i: DMX:%i fine:%i from/to add:%u/%u\tmin/max: %lf/%lf ) **\n", i,_dim.dmxchannel, _dim.finedmxchannel,_dim.mindmx, _dim.maxdmx,  _dim.minval, _dim.maxval );
	}
}
