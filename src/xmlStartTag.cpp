#include "DDFreader.h"

void DDFreader::startTag(String tagName){

	if(tagName.startsWith(TAG_DEVICE) == false){
		#ifdef DDFREADER_DEBUG
		Serial.printf("xml is not a device. Tag:%s\n", tagName.c_str());
		#endif
		// return;	//return if xml is not a device
	}
	
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL) == true){	//start new colorwheel
		deviceInfo.colorwheelCount++;
		DDFcolorwheel* newColorwheel = new DDFcolorwheel[deviceInfo.colorwheelCount];	//declare new array
		std::copy(colorwheelArray, colorwheelArray + std::min(deviceInfo.colorwheelCount-1, deviceInfo.colorwheelCount), newColorwheel);	//copy to new array
		colorwheelArray = newColorwheel;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Colorwheel (#%u):\n",deviceInfo.colorwheelCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == true){
		currentTag = tagName;
	}else if(tagName.startsWith(TAG_FUNCTIONS_COLORWHEEL_RAINBOW) == true){
		currentTag = tagName;
	}else if(tagName.startsWith(TAG_FUNCTIONS_COLORWHEEL_RANDOM) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_DIMMER) == true){
		deviceInfo.dimmerCount++;
		DDFdimmer* newDimmer = new DDFdimmer[deviceInfo.dimmerCount];	//declare new array
		std::copy(dimmerArray, dimmerArray + std::min(deviceInfo.dimmerCount-1, deviceInfo.dimmerCount), newDimmer);	//copy to new array
		delete[] dimmerArray;	//delte old array
		dimmerArray = newDimmer;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Dimmer (#%u):\n",deviceInfo.dimmerCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_FOCUS) == true){
		deviceInfo.focusCount++;
		DDFfocus* newFocus = new DDFfocus[deviceInfo.focusCount];	//declare new array
		std::copy(focusArray, focusArray + std::min(deviceInfo.focusCount-1, deviceInfo.focusCount), newFocus);	//copy to new array
		delete[] focusArray;	//delte old array
		focusArray = newFocus;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Focus (#%u):\n",deviceInfo.focusCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_FROST) == true){
		deviceInfo.frostCount++;
		DDFfrost* newFrost = new DDFfrost[deviceInfo.frostCount];	//declare new array
		std::copy(frostArray, frostArray + std::min(deviceInfo.frostCount-1, deviceInfo.frostCount), newFrost);	//copy to new array
		delete[] frostArray;	//delte old array
		frostArray = newFrost;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Frost (#%u):\n",deviceInfo.frostCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_GOBOWHEEL) == true){
		deviceInfo.gobowheelCount = 1;
		// DDFgobowheel* newColorwheel = new DDFcolorwheel[deviceInfo.colorwheelCount];	//declare new array
		// std::copy(colorwheelArray, colorwheelArray + std::min(deviceInfo.colorwheelCount-1, deviceInfo.colorwheelCount), newColorwheel);	//copy to new array
		// colorwheelArray = newColorwheel;	//copy to old array
		// currentTag = tagName;
		// #ifdef DDFREADER_DEBUG
		// Serial.printf("new Colorwheel (#%u):\n",deviceInfo.colorwheelCount-1);
		// #endif
		

	}else if(tagName.equals(TAG_FUNCTIONS_MATRIX) == true){
		deviceInfo.matrixCount++;
		DDFmatrix* newMatrix = new DDFmatrix[deviceInfo.matrixCount];	//declare new array
		std::copy(matrixArray, matrixArray + std::min(deviceInfo.matrixCount-1, deviceInfo.matrixCount), newMatrix);	//copy to new array
		delete[] matrixArray;	//delte old array
		matrixArray = newMatrix;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Matrix (#%u):\n",deviceInfo.matrixCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_POSITION) == true){
		deviceInfo.positionCount++;
		DDFposition* newPosition = new DDFposition[deviceInfo.positionCount];	//declare new array
		std::copy(positionArray, positionArray + std::min(deviceInfo.positionCount-1, deviceInfo.positionCount), newPosition);	//copy to new array
		delete[] positionArray;	//delte old array
		positionArray = newPosition;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Position (#%u):\n",deviceInfo.positionCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_POSITION_PAN) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_POSITION_TILT) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_PRISM) == true){
		deviceInfo.prismCount++;
		DDFprism* newPrism = new DDFprism[deviceInfo.prismCount];	//declare new array
		std::copy(prismArray, prismArray + std::min(deviceInfo.prismCount-1, deviceInfo.prismCount), newPrism);	//copy to new array
		delete[] prismArray;	//delte old array
		prismArray = newPrism;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Prism (#%u):\n",deviceInfo.prismCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_PTSPEED) == true){
		deviceInfo.ptspeedCount++;
		DDFptspeed* newPtspeed = new DDFptspeed[deviceInfo.ptspeedCount];	//declare new array
		std::copy(ptspeedArray, ptspeedArray + std::min(deviceInfo.ptspeedCount-1, deviceInfo.ptspeedCount), newPtspeed);	//copy to new array
		delete[] ptspeedArray;	//delte old array
		ptspeedArray = newPtspeed;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Ptspeed (#%u):\n",deviceInfo.ptspeedCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_RAW) == true){
		deviceInfo.rawCount++;
		DDFraw* newRaw = new DDFraw[deviceInfo.rawCount];	//declare new array
		std::copy(rawArray, rawArray + std::min(deviceInfo.rawCount-1, deviceInfo.rawCount), newRaw);	//copy to new array
		delete[] rawArray;	//delte old array
		rawArray = newRaw;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Raw (#%u):\n",deviceInfo.rawCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_RGB) == true){
		deviceInfo.rgbCount++;
		DDFrgb* newRgb = new DDFrgb[deviceInfo.rgbCount];	//declare new array
		std::copy(rgbArray, rgbArray + std::min(deviceInfo.rgbCount-1, deviceInfo.rgbCount), newRgb);	//copy to new array
		delete[] rgbArray;	//delte old array
		rgbArray = newRgb;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Rgb (#%u):\n",deviceInfo.rgbCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_SHUTTER) == true){
		deviceInfo.shutterCount++;
		DDFshutter* newShutter = new DDFshutter[deviceInfo.shutterCount];	//declare new array
		std::copy(shutterArray, shutterArray + std::min(deviceInfo.shutterCount-1, deviceInfo.shutterCount), newShutter);	//copy to new array
		delete[] shutterArray;	//delte old array
		shutterArray = newShutter;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Shutter (#%u):\n",deviceInfo.shutterCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_STEP) == true){
		deviceInfo.stepfuncCount++;
		DDFstep* newStepfunc = new DDFstep[deviceInfo.stepfuncCount];	//declare new array
		std::copy(stepfuncArray, stepfuncArray + std::min(deviceInfo.stepfuncCount-1, deviceInfo.stepfuncCount), newStepfunc);	//copy to new array
		delete[] stepfuncArray;	//delte old array
		stepfuncArray = newStepfunc;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Step (#%u):\n",deviceInfo.stepfuncCount-1);
		#endif


	}else if(tagName.equals(TAG_FUNCTIONS_STROBE) == true){
		deviceInfo.strobeCount++;
		DDFstrobe* newStrobefunc = new DDFstrobe[deviceInfo.strobeCount];	//declare new array
		std::copy(strobeArray, strobeArray + std::min(deviceInfo.strobeCount-1, deviceInfo.strobeCount), newStrobefunc);	//copy to new array
		delete[] strobeArray;	//delte old array
		strobeArray = newStrobefunc;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Strobe (#%u):\n",deviceInfo.strobeCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_STROBE_RANGE) == true){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_ZOOM) == true){
		deviceInfo.zoomCount++;
		DDFzoom* newZoom = new DDFzoom[deviceInfo.zoomCount];	//declare new array
		std::copy(zoomArray, zoomArray + std::min(deviceInfo.zoomCount-1, deviceInfo.zoomCount), newZoom);	//copy to new array
		delete[] zoomArray;	//delte old array
		zoomArray = newZoom;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Zoom (#%u):\n",deviceInfo.zoomCount-1);
		#endif
	}else{
		currentTag = TAG_NONE;
	}
}