/*
 * DDFptspeeds.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFPTSPEEDS_H_
#define LIBRARIES_DDFREADER_DDFPTSPEEDS_H_
#include "DDFptspeed.h"

class DDFptspeeds{
public:
	DDFptspeeds(DDFptspeed* array, uint16_t size){
		_array = new DDFptspeed[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFptspeeds(){
		delete[] _array;
	}

	void setSpeed(DDFptspeed function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFptspeed getSpeed(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFptspeed empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFptspeed* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFPTSPEEDS_H_ */
