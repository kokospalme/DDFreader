/*
 * DDFmarix.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef DDFMATRIX_H_
#define DDFMATRIX_H_
#include <Arduino.h>
#include <DDF_defines.h>
#include "DDFrgb.h"

class DDFmatrix{
public:
	bool exist = false;
	int dmxchannel = -1;
	int finedmxchannel = -1;
	
	DDFmatrix(uint8_t sizeX = 1,uint8_t sizeY = 1, uint8_t matrixtype = matrix_cartesian){
		_size = sizeX * sizeY;
		if(_size > 512){
			_size = 512;
			Serial.println("max matrix size reached: 512 px");
		}
		_matrixtype = matrixtype;
		_arrayPixels = new matrixPixel_t[_size];
	}
	virtual ~DDFmatrix(){
		delete[] _arrayPixels;
	}

	void setRgb(DDFrgb function, uint16_t no, uint16_t x_angle, uint16_t y_distance){
		if(no < _size){
			_arrayPixels[no].pixel = function;

		}
	}

	matrixPixel_t getPixel(uint16_t no){
		if(no < _size)return _arrayPixels[no];
		else{
			matrixPixel_t emptyPixel;
			return emptyPixel;
		}
	}



	uint16_t getSize(){ return _size;}

private:
	matrixPixel_t* _arrayPixels;
	uint8_t _matrixtype = matrix_cartesian;
	uint16_t _size = 0;

};


#endif /*  DDFMATRIX_H_ */
