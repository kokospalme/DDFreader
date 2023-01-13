/*
 * DDFdimmres.h
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFDIMMRES_H_
#define LIBRARIES_DDFREADER_DDFDIMMRES_H_
#include "DDFdimmer.h"

class DDFdimmers{
public:
	DDFdimmers(DDFdimmer* array, uint16_t size){
		_array = new DDFdimmer[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFdimmers(){
		delete[] _array;
	}

	void setDimmer(DDFdimmer function, uint16_t no){
		if(no < _size) _array[no] = function;
		_array[no].exist = true;
	}

	DDFdimmer getDimmer(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFdimmer empty;
			return empty;
		}
	}

	void setVal(uint16_t no, double val){
		if(no < _size )  _array[no].value = val;
	}

	uint16_t getSize(){ return _size;}

private:
	DDFdimmer* _array;
	uint16_t _size = 0;

};

#endif /* LIBRARIES_DDFREADER_DDFDIMMRES_H_ */
