/*
 * DDFfrosts.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef DDFFROSTS_H_
#define DDFFROSTS_H_
#include "DDFfrost.h"

class DDFfrosts{
public:
	DDFfrosts(DDFfrost* array, uint16_t size){
		_array = new DDFfrost[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFfrosts(){
		delete[] _array;
	}

	void setFrost(DDFfrost function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFfrost getFrost(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFfrost empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFfrost* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFFROSTS_H_ */
