/*
 * DDFzooms.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFZOOMS_H_
#define LIBRARIES_DDFREADER_DDFZOOMS_H_
#include "DDFzoom.h"

class DDFzooms{
public:
	DDFzooms(DDFzoom* array, uint16_t size){
		_array = new DDFzoom[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFzooms(){
		delete[] _array;
	}

	void setZoom(DDFzoom function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFzoom getZoom(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFzoom empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFzoom* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFZOOMS_H_ */
