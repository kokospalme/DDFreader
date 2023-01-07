/*
 * DDFstep.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFSTEP_H_
#define LIBRARIES_DDFREADER_DDFSTEP_H_
#include <Arduino.h>
#include "DDF_defines.h"

class DDFstep{
public:
	bool exist = false;
	int dmxchannel = -1;
	int finedmxchannel = -1;
	
	DDFstep(){//singlestep for first init
		_array = new singlestep_t;
	}
	DDFstep(singlestep_t* array, uint16_t size){
		_array = new singlestep_t[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFstep(){
		delete[] _array;
	}

	void setSinglestep(singlestep_t function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	singlestep_t getSinglestep(uint16_t no){
		if(no < _size)return _array[no];
		else{
			singlestep_t empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}
private:
	singlestep_t* _array;
	uint8_t steptype = steps_color;
	uint8_t _size = 0;	//
};



#endif /* LIBRARIES_DDFREADER_DDFSTEP_H_ */
