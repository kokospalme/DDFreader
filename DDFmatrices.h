/*
 * DDFmatrices.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFMATRICES_H_
#define LIBRARIES_DDFREADER_DDFMATRICES_H_
#include "DDFmatrix.h"

class DDFmatrices{
public:
	DDFmatrices(DDFmatrix* array, uint16_t size){
		_matrixSizes = new uint8_t[size];	//array for sizes of matrices
		_array = new DDFmatrix[size];
		for(int i = 0; i < size;i++){
			_array[i] = array[i];
		}
	}
	virtual ~DDFmatrices(){
		delete[] _array;
	}

	void setMatrix(DDFmatrix function, uint16_t no){
		if(no < _size) _array[no] = function;
	}

	DDFmatrix getMatrix(uint16_t no){
		if(no < _size)return _array[no];
		else{
			DDFmatrix empty(1,1,0);
			return empty;
		}
	}

	uint16_t getSize(){ return _size;}

private:
	DDFmatrix* _array;
	uint8_t* _matrixSizes;	//
	uint16_t _size = 0;

};





#endif /* LIBRARIES_DDFREADER_DDFMATRICES_H_ */
