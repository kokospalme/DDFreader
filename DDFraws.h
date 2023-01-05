/*
 * DDFraws.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFRAWS_H_
#define LIBRARIES_DDFREADER_DDFRAWS_H_
#include "DDFraw.h"

class DDFraws{
public:
	DDFraws(DDFraw* array, uint16_t size){
		_array = new DDFraw[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFraws(){
		delete[] _array;
	}

	void setRaw(DDFraw function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFraw getRaw(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFraw empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFraw* _array;
	uint16_t _size = 0;

};





#endif /* LIBRARIES_DDFREADER_DDFRAWS_H_ */
