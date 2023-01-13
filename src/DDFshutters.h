/*
 * DDFshutters.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFSHUTTERS_H_
#define LIBRARIES_DDFREADER_DDFSHUTTERS_H_
#include "DDFshutter.h"

class DDFshutters{
public:
	DDFshutters(DDFshutter* array, uint16_t size){
		_array = new DDFshutter[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFshutters(){
		delete[] _array;
	}

	void setShutter(DDFshutter function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFshutter getShutter(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFshutter empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFshutter* _array;
	uint16_t _size = 0;

};



#endif /* LIBRARIES_DDFREADER_DDFSHUTTERS_H_ */
