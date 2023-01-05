/*
 * DDFfocusseses.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFFOCUSSESES_H_
#define LIBRARIES_DDFREADER_DDFFOCUSSESES_H_
#include "DDFfocus.h"

class DDFfocusses{
public:
	DDFfocusses(DDFfocus* array, uint16_t size){
		_array = new DDFfocus[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFfocusses(){
		delete[] _array;
	}

	void setfocus(DDFfocus function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFfocus getfocus(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFfocus empty;
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFfocus* _array;
	uint16_t _size = 0;

};




#endif /* LIBRARIES_DDFREADER_DDFfocussesES_H_ */
