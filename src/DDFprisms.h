/*
 * DDFprisms.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFPRISMS_H_
#define LIBRARIES_DDFREADER_DDFPRISMS_H_
#include "DDFprism.h"

class DDFprisms{
public:
	DDFprisms(DDFprism* array, uint16_t size){
		_array = new DDFprism[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFprisms(){
		delete[] _array;
	}

	void setPrism(DDFprism function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFprism getPrism(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFprism empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFprism* _array;
	uint16_t _size = 0;

};



#endif /* LIBRARIES_DDFREADER_DDFPRISMS_H_ */
