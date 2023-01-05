/*
 * DDFfunctions.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 *
 *      template example from:
 *      https://stackoverflow.com/questions/64269298/arrays-of-template-class-objects
 */

#ifndef LIBRARIES_DDFREADER_DDF_FUNCTION_H_
#define LIBRARIES_DDFREADER_DDF_FUNCTION_H_

#include <Arduino.h>
#include <DDFdimmer.h>
#include <DDFfocus.h>
#include <DDFposition.h>
#include <DDFrgb.h>
#include <DDFstep.h>


class AbstractDDFfunction{
public:
	template <class T>
	void Set(T inval);
	template <class T>
	void Get(T* retval);
};

template <class T>
class DDFfunction: public AbstractDDFfunction{
public:
	void Set(T inval){
		storage = inval;
	}
	void Get(T* retval){
		*retval = storage;
	}
private:
	T storage = {};
};

// Manually pointing base overloads to template methods
template <class T> void AbstractDDFfunction::Set(T inval){
	static_cast<DDFfunction<T>*>(this)->Set(inval);
}

template <class T> void AbstractDDFfunction::Get(T* retval){
	static_cast<DDFfunction<T>*>(this)->Get(retval);
}


#endif /* LIBRARIES_DDFREADER_DDF_FUNCTION_H_ */
