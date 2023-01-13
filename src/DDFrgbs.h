/*
 * DDFrgbs.h
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFRGBS_H_
#define LIBRARIES_DDFREADER_DDFRGBS_H_
#include "DDFrgb.h"

class DDFrgbs{
public:
	DDFrgbs(DDFrgb* array, uint16_t size){
		_array = new DDFrgb[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFrgbs(){
		delete[] _array;
	}

	void setRgb(DDFrgb function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFrgb getRgb(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFrgb emptyRgb;
			return emptyRgb;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFrgb* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFRGBS_H_ */
