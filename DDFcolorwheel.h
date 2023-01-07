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
	int dmxchannel = -1;
	int rainbowStopMindmx = -1;
	int rainbowStopMaxdmx = -1;
	int rainbowCwMindmx = -1;
	int rainbowCwMaxdmx = -1;
	double rainbowCwMinvalue = -1;
	double rainbowCwMaxvalue = -1;
	int rainbowCCwMindmx = -1;
	int rainbowCCwMaxdmx = -1;
	double rainbowCCwMinvalue = -1;
	double rainbowCCwMaxvalue = -1;

	virtual ~DDFcolorwheel(){
		delete[] _colorArray;
		delete[] _colorwheelArray;
	}

	void setGobowheel(colorwheel_t wheel, uint16_t no){
		if(no < _sizeWheels) _colorwheelArray[no] = wheel;
	}

	colorwheel_t getGobowheel(uint16_t no){
		if(no < _sizeWheels)return _colorwheelArray[no];
		else{
			colorwheel_t empty;
			return empty;
		}
	}

	void setGobo(singlecolor_t color, uint16_t wheelNo, uint16_t colorNo){
		if(wheelNo < _sizeWheels && colorNo < _colorwheelArray[wheelNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < wheelNo; i++){
				_no += _colorwheelArray[i].size;
			}
			_no += colorNo;
			if(_no <_sizeGobos){
				_colorArray[_no] = color;
			}
		}
	}

	singlecolor_t getGobo(uint16_t wheelNo, uint16_t colorNo){
		if(wheelNo < _sizeWheels && colorNo < _colorwheelArray[wheelNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < wheelNo; i++){
				_no += _colorwheelArray[i].size;
			}
			_no += colorNo;
			return _colorArray[_no];
		}
		else{
			singlecolor_t empty;
			return empty;
		}
	}

	uint16_t getSizeWheels(){ return _sizeWheels;}
	uint16_t getSizeWheel(uint16_t wheelNo){
		if(wheelNo < _sizeWheels) return _colorwheelArray[wheelNo].size;
		else return 0;
	}

private:
	singlecolor_t* _colorArray;
	colorwheel_t* _colorwheelArray;
	uint16_t _sizeWheels = 0;
	uint16_t _sizeGobos = 0;

};

#endif /* DDFCOLORWHEEL_H_ */
