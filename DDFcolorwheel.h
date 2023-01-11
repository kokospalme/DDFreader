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
		delete[] _singlecolorArray;
		delete[] _colorwheelArray;
	}

	void setColorwheel(colorwheel_t wheel, uint16_t no){
		if(no < _sizeWheels) _colorwheelArray[no] = wheel;
	}

	colorwheel_t getColorwheel(uint16_t no){
		if(no < _sizeWheels)return _colorwheelArray[no];
		else{
			colorwheel_t empty;
			return empty;
		}
	}

	void setColors(singlecolor_t* colorArray){
		_singlecolorArray = colorArray;
	}

	singlecolor_t getSinglecolor(uint16_t wheelNo, uint16_t colorNo){
		if(wheelNo < _sizeWheels && colorNo < _colorwheelArray[wheelNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < wheelNo; i++){
				_no += _colorwheelArray[i].size;
			}
			_no += colorNo;
			return _singlecolorArray[_no];
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
	singlecolor_t* _singlecolorArray;
	colorwheel_t* _colorwheelArray;
	uint16_t _sizeWheels = 0;
	uint16_t _sizeGobos = 0;

};

#endif /* DDFCOLORWHEEL_H_ */
