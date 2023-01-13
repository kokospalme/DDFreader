/*
 * DDFdevice.cpp
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */


#include "DDFdevice.h"

DDFdevice::DDFdevice(ddfInformation_t ddfInfo, deviceInformation_t deviceInfo){

	_ddfInfo = ddfInfo;
	_deviceInfo = deviceInfo;

	_colorwheelCount = deviceInfo.colorwheelCount;	//
	_singlecolorCount = deviceInfo.singlecolorCount;
	_dimmerCount = deviceInfo.dimmerCount;
	_focusCount = deviceInfo.focusCount;
	_frostCount = deviceInfo.frostCount;
	_gobowheelCount = deviceInfo.gobowheelCount;
	_singlegoboCount = deviceInfo.singlegoboCount;
	_matrixCount = deviceInfo.matrixCount;
	_positionCount = deviceInfo.positionCount;
	_prismCount = deviceInfo.prismCount;
	_ptspeedCount = deviceInfo.ptspeedCount;
	_rawCount = deviceInfo.rawCount;
	_rgbCount = deviceInfo.rgbCount;
	_shutterCount = deviceInfo.shutterCount;
	_stepfuncCount = deviceInfo.stepfuncCount;
	_singlestepCount = deviceInfo.singlestepCount;
	_zoomCount = deviceInfo.zoomCount;


	_functionCount = _dimmerCount + _focusCount + _frostCount + _gobowheelCount + _matrixCount + _positionCount + _prismCount + _ptspeedCount + _rawCount + _rgbCount + _shutterCount + _stepfuncCount + _zoomCount;
	fnc_array = new AbstractDDFfunction[_functionCount];	//ToDo: obsolet, da nicht abstrakt sein muss?//abtract function array ToDo

	DDFcolorwheel _colorwheelArray[_colorwheelCount];	//temp array
	singlecolor_t _singlecolorArray[_singlecolorCount];

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

	// _colorwheels = new DDFcolorwheels(_colorArray, _singlecolorCount, _colorwheelArray, _colorwheelCount);	//ToDo: obsolet?? assign new 
	_colorwheels = new DDFcolorwheel[_deviceInfo.colorwheelCount];


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

void DDFdevice::addColorwheels(DDFcolorwheel* array){
	
	std::copy(_colorwheels, _colorwheels + std::min(_deviceInfo.colorwheelCount, _deviceInfo.colorwheelCount), array);	//copy to new array
	// delete[] shutterArray;	//delte old array
	// shutterArray = newShutter;	//copy to old array
	// currentTag = tagName;
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
	// Serial.printf("** DDF device (%s [%s]) **\n", _model.c_str(), _vendor.c_str());
	for(int i = 0; i < _rgbCount; i++){
		DDFdimmer _dim = _dimmers->getDimmer(i);
		Serial.printf("** Dimmer%i: DMX:%i fine:%i from/to add:%u/%u\tmin/max: %lf/%lf ) **\n", i,_dim.dmxchannel, _dim.finedmxchannel,_dim.mindmx, _dim.maxdmx,  _dim.minval, _dim.maxval );
	}
}
