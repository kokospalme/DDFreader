/*
 * DDFcolorwheels.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFCOLORWHEELS_H_
#define LIBRARIES_DDFREADER_DDFCOLORWHEELS_H_

class DDFcolorwheels{
public:
	DDFcolorwheels(singlecolor_t* colors, uint16_t colorCount, colorwheel_t* colorwheels, uint16_t wheelsCount){
		_colorArray = new singlecolor_t[colorCount];
		_colorwheelArray = new colorwheel_t[wheelsCount];

		_sizeGobos = colorCount;
		_sizeWheels = wheelsCount;


		for(int i = 0; i < wheelsCount;i++){
			_colorwheelArray[i] = colorwheels[i];
		}

		for(int i = 0; i < colorCount; i++){
			_colorArray[i] = colors[i];
		}


	}
	virtual ~DDFcolorwheels(){
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

#endif /* LIBRARIES_DDFREADER_DDFCOLORWHEELS_H_ */
