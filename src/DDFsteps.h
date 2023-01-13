/*
 * DDFsteps.h
 *
 *  Created on: 20 Nov 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFSTEPS_H_
#define LIBRARIES_DDFREADER_DDFSTEPS_H_

class DDFsteps{
public:
	DDFsteps(singlestep_t* steps, uint16_t stepCount, stepfunc_t* stepfuncs, uint16_t funcCount){

		_stepArray = new singlestep_t[stepCount];
		_stepfuncArray = new stepfunc_t[funcCount];

		_sizeSteps = stepCount;
		_sizeFuncs = funcCount;


		for(int i = 0; i < funcCount;i++){
			_stepfuncArray[i] = stepfuncs[i];
		}

		for(int i = 0; i < stepCount; i++){
			_stepArray[i] = steps[i];
		}


	}
	virtual ~DDFsteps(){
		delete[] _stepArray;
		delete[] _stepfuncArray;
	}

	void setStepfunc(stepfunc_t stepFunc, uint16_t no){
		if(no < _sizeFuncs) _stepfuncArray[no] = stepFunc;
	}

	stepfunc_t getStepfunc(uint16_t no){
		if(no < _sizeFuncs)return _stepfuncArray[no];
		else{
			stepfunc_t empty;
			return empty;
		}
	}

	void setStep(singlestep_t step, uint16_t stepfuncNo, uint16_t stepNo){
		if(stepfuncNo < _sizeFuncs && stepNo < _stepfuncArray[stepfuncNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < stepfuncNo; i++){
				_no += _stepfuncArray[i].size;
			}
			_no += stepNo;
			if(_no <_sizeSteps){
				_stepArray[_no] = step;
			}
		}
	}

	singlestep_t getStep(uint16_t funcNo, uint16_t stepNo){
		if(funcNo < _sizeSteps && stepNo < _stepfuncArray[funcNo].size){
			uint16_t _no = 0;
			for(int i = 0; i < funcNo; i++){
				_no += _stepfuncArray[i].size;
			}
			_no += stepNo;
			return _stepArray[_no];
		}
		else{
			singlestep_t empty;
			return empty;
		}
	}

	uint16_t getSizeFuncs(){ return _sizeFuncs;}
	uint16_t getSizeFunc(uint16_t funcNo){
		if(funcNo < _sizeFuncs) return _stepfuncArray[funcNo].size;
		else return 0;
	}

private:
	singlestep_t* _stepArray;
	stepfunc_t* _stepfuncArray;
	uint16_t _sizeFuncs = 0;
	uint16_t _sizeSteps = 0;

};



#endif /* LIBRARIES_DDFREADER_DDFSTEPS_H_ */
