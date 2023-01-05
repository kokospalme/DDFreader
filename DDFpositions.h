/*
 * DDFpositions.h
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */

#ifndef DDFPOSITIONS_H_
#define DDFPOSITIONS_H_

#include "DDFposition.h"

class DDFpositions{
public:
	DDFpositions(DDFposition* array, uint16_t size){
		_array = new DDFposition[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFpositions(){
		delete[] _array;
	}

	void setPosition(DDFposition function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFposition getPosition(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFposition empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFposition* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFPOSITIONS_H_ */
