/*
 * DDFgobowheels.h
 *
 *  Created on: 21 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFGOBOWHEELS_H_
#define LIBRARIES_DDFREADER_DDFGOBOWHEELS_H_

class DDFgobowheels{
public:
	DDFgobowheels(singlegobo_t* gobos, uint16_t goboCount, gobowheel_t* gobowheels, uint16_t wheelsCount){
		_goboArray = new singlegobo_t[goboCount];
		_gobowheelArray = new gobowheel_t[wheelsCount];

		_sizeGobos = goboCount;
		_sizeWheels = wheelsCount;


		for(int i = 0; i < wheelsCount;i++){
			_gobowheelArray[i] = gobowheels[i];
		}

		for(int i = 0; i < goboCount; i++){
			_goboArray[i] = gobos[i];
		}


	}
	virtual ~DDFgobowheels(){
		delete[] _goboArray;
		delete[] _gobowheelArray;
	}

	void setGobowheel(gobowheel_t wheel, uint16_t no){
		if(no < _sizeWheels) _gobowheelArray[no] = wheel;
	}

	gobowheel_t getGobowheel(uint16_t no){
		if(no < _sizeWheels)return _gobowheelArray[no];
		else{
			gobowheel_t empty;
			return empty;
		}
	}

	void setGobo(singlegobo_t gobo, uint16_t wheelNo, uint16_t goboNo){
		if(wheelNo < _sizeWheels && goboNo < _gobowheelArray[wheelNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < wheelNo; i++){
				_no += _gobowheelArray[i].size;
			}
			_no += goboNo;
			if(_no <_sizeGobos){
				_goboArray[_no] = gobo;
			}
		}
	}

	singlegobo_t getGobo(uint16_t wheelNo, uint16_t goboNo){
		if(wheelNo < _sizeWheels && goboNo < _gobowheelArray[wheelNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < wheelNo; i++){
				_no += _gobowheelArray[i].size;
			}
			_no += goboNo;
			return _goboArray[_no];
		}
		else{
			singlegobo_t empty;
			return empty;
		}
	}

	uint16_t getSizeWheels(){ return _sizeWheels;}
	uint16_t getSizeWheel(uint16_t wheelNo){
		if(wheelNo < _sizeWheels) return _gobowheelArray[wheelNo].size;
		else return 0;
	}

private:
	singlegobo_t* _goboArray;
	gobowheel_t* _gobowheelArray;
	uint16_t _sizeWheels = 0;
	uint16_t _sizeGobos = 0;

};





#endif /* LIBRARIES_DDFREADER_DDFGOBOWHEELS_H_ */
