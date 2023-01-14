#include "DDFreader.h"

void DDFreader::processDmxchannel(String data){
	int dataInt = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_COLORWHEEL ){
		dataInt = (int) data.toInt();
		colorwheel.dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",colorwheel.dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_DIMMER ){
		dataInt = (int) data.toInt();
		dimmerArray[deviceInfo.dimmerCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",dimmerArray[deviceInfo.dimmerCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_FOCUS ){
		dataInt = (int) data.toInt();
		focusArray[deviceInfo.focusCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",focusArray[deviceInfo.focusCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_FROST ){
		dataInt = (int) data.toInt();
		frostArray[deviceInfo.frostCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",frostArray[deviceInfo.frostCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL ){
		dataInt = (int) data.toInt();
		gobowheelArray[deviceInfo.gobowheelCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",gobowheelArray[deviceInfo.gobowheelCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].pan_dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tpan dmxchannel: %u\n",positionArray[deviceInfo.positionCount-1].pan_dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].tilt_dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\ttilt dmxchannel: %u\n",positionArray[deviceInfo.positionCount-1].tilt_dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_PRISM ){
		dataInt = (int) data.toInt();
		prismArray[deviceInfo.prismCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",prismArray[deviceInfo.prismCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_PTSPEED ){
		dataInt = (int) data.toInt();
		ptspeedArray[deviceInfo.ptspeedCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",ptspeedArray[deviceInfo.ptspeedCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RAW ){
		dataInt = (int) data.toInt();
		rawArray[deviceInfo.rawCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",rawArray[deviceInfo.rawCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_R ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].redDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tR dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].redDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_G ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].greenDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tG dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].greenDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_B ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].blueDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tB dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].blueDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_W ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tW dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_A ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].amberDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tA dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].amberDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_U ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].uvDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tU dmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].uvDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_SHUTTER ){
		dataInt = (int) data.toInt();
		shutterArray[deviceInfo.shutterCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",shutterArray[deviceInfo.shutterCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_STEP ){
		dataInt = (int) data.toInt();
		stepfuncArray[deviceInfo.stepfuncCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",stepfuncArray[deviceInfo.stepfuncCount-1].dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_STROBE ){
		dataInt = (int) data.toInt();
		strobe.dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",strobe.dmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_ZOOM ){
		dataInt = (int) data.toInt();
		zoomArray[deviceInfo.zoomCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",zoomArray[deviceInfo.zoomCount-1].dmxchannel);
		#endif
	}
}

void DDFreader::processFinedmx(String data){
	int dataInt = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_COLORWHEEL ){
		//do nothing (no finedmx for colorwheels)
	}else if(currentTag == TAG_FUNCTIONS_DIMMER ){
		dataInt = (int) data.toInt();
		dimmerArray[deviceInfo.dimmerCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",dimmerArray[deviceInfo.dimmerCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_FOCUS ){
		dataInt = (int) data.toInt();
		focusArray[deviceInfo.focusCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",focusArray[deviceInfo.focusCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_FROST ){
		dataInt = (int) data.toInt();
		frostArray[deviceInfo.frostCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",frostArray[deviceInfo.frostCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL ){
		//do nothing (no finedmx for gobowheels)
	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].pan_finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tpan finedmxchannel: %u\n",positionArray[deviceInfo.positionCount-1].pan_finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].tilt_finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\ttilt finedmxchannel: %u\n",positionArray[deviceInfo.positionCount-1].tilt_finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_PRISM ){
		dataInt = (int) data.toInt();
		prismArray[deviceInfo.prismCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",prismArray[deviceInfo.prismCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_PTSPEED ){
		dataInt = (int) data.toInt();
		ptspeedArray[deviceInfo.ptspeedCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",ptspeedArray[deviceInfo.ptspeedCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RAW ){
		dataInt = (int) data.toInt();
		rawArray[deviceInfo.rawCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",rawArray[deviceInfo.rawCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_R ){
		dataInt = (int) data.toInt();
		rawArray[deviceInfo.rawCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tR finedmxchannel: %u\n",rawArray[deviceInfo.rawCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_G ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].greenDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tG finedmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].greenDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_B ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].blueDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tB finedmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].blueDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_W ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tW finedmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_A ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].amberDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tA finedmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].amberDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_RGB_U ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].uvDmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tU finedmxchannel: %u\n",rgbArray[deviceInfo.rgbCount-1].uvDmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_SHUTTER ){
		dataInt = (int) data.toInt();
		shutterArray[deviceInfo.shutterCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u):\n",shutterArray[deviceInfo.shutterCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_STEP ){
		dataInt = (int) data.toInt();
		stepfuncArray[deviceInfo.stepfuncCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",stepfuncArray[deviceInfo.stepfuncCount-1].finedmxchannel);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_ZOOM ){
		dataInt = (int) data.toInt();
		zoomArray[deviceInfo.zoomCount-1].finedmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tfinedmxchannel: %u\n",zoomArray[deviceInfo.zoomCount-1].finedmxchannel);
		#endif

	}
}

void DDFreader::processRange(String data){	//attribute "range"
	int dataInt = 0;
	double dataDouble = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL_INDEX_RANGE ){
		dataDouble = (double) data.toDouble();
		gobowheelArray[deviceInfo.gobowheelCount-1].indexRange = dataDouble;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tindex Range: %u\n",gobowheelArray[deviceInfo.gobowheelCount-1].indexRange);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN_RANGE ){
		dataDouble = (double) data.toDouble();
		positionArray[deviceInfo.positionCount-1].pan_range = dataDouble;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tpan Range: %u\n",positionArray[deviceInfo.positionCount-1].pan_range);
		#endif

	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT_RANGE ){
		dataDouble = (double) data.toDouble();
		positionArray[deviceInfo.positionCount-1].tilt_range = dataDouble;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\ttilt Range: %u\n",positionArray[deviceInfo.positionCount-1].tilt_range);
		#endif

	}
}

void DDFreader::processType(String data){	//process attribute "type"

	if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true){	//colorwheel step
		if(data.equals(STEPTYPE_COLOR) == true){	//if type is "color": increase singlecolor array
			deviceInfo.singlecolorCount++;
			singlecolor_t* newSinglecolor = new singlecolor_t[deviceInfo.singlecolorCount];	//declare new array
			std::copy(colorArray, colorArray + std::min(deviceInfo.singlecolorCount-1, deviceInfo.singlecolorCount), newSinglecolor);	//copy to new array
			colorArray = newSinglecolor;	//copy to old array
			colorArray[deviceInfo.singlecolorCount-1].wheelNo = deviceInfo.colorwheelCount-1;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\t==new step(color) (#%u):\n",deviceInfo.singlecolorCount-1);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == true ){	//colorwheel rainbow step
		if(data == ROTATIONTYPE_STOP){
			currentRotationtype = ROTATIONTYPE_STOP;
		}else if(data == ROTATIONTYPE_CLOCKWISE){
			currentRotationtype = ROTATIONTYPE_CLOCKWISE;
		}else if(data == ROTATIONTYPE_COUNTERCLOCKWISE){
			currentRotationtype = ROTATIONTYPE_COUNTERCLOCKWISE;
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == true ){	//colorwheel rainbow step
		if(data == ROTATIONTYPE_STOP){
			currentRainbowtype = ROTATIONTYPE_STOP;
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == true){	//colorwheel random step
		if(data.equals(RANDOM_TYPE_FAST) == true){	//fast
			currentRandomtype = RANDOM_TYPE_FAST;
		}else if(data.equals(RANDOM_TYPE_MEDIUM) == true){	//medium
			currentRandomtype = RANDOM_TYPE_MEDIUM;
		}else if(data.equals(RANDOM_TYPE_SLOW) == true){	//slow
			currentRandomtype = RANDOM_TYPE_SLOW;
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_SHUTTER_STEP) == true ){	//shutter step
		if(data.equals(SHUTTERTYPE_OPEN) == true){	//if type is "open": increase shutterstep array
			deviceInfo.shutterstepCount++;
			shutterstep_t* newShutterstep = new shutterstep_t[deviceInfo.shutterstepCount];	//declare new array
			std::copy(shutterstepArray, shutterstepArray + std::min(deviceInfo.shutterstepCount-1, deviceInfo.shutterstepCount), newShutterstep);	//copy to new array
			shutterstepArray = newShutterstep;	//copy to old array
			shutterstepArray[deviceInfo.shutterstepCount-1]. = deviceInfo.shutterstepCount-1;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\t==new step(open) (#%u):\n",deviceInfo.shutterstepCount-1);
			#endif

		}else if(data.equals(SHUTTERTYPE_CLOSED) == true){	//if type is "closed": increase shutterstep array
			deviceInfo.shutterstepCount++;
			shutterstep_t* newShutterstep = new shutterstep_t[deviceInfo.shutterstepCount];	//declare new array
			std::copy(shutterstepArray, shutterstepArray + std::min(deviceInfo.shutterstepCount-1, deviceInfo.shutterstepCount), newShutterstep);	//copy to new array
			shutterstepArray = newShutterstep;	//copy to old array
			shutterstepArray[deviceInfo.shutterstepCount-1]. = deviceInfo.shutterstepCount-1;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\t==new step(closed) (#%u):\n",deviceInfo.shutterstepCount-1);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_STROBE_RANGE) == true ){	//strobe curve type
		if(data.equals(STROBETYPE_LINEAR) == true || data.equals(STROBETYPE_PULSE) == true || data.equals(STROBETYPE_RANDOM) == true){
			currentCurvetype = data;
		}
	}

}

void DDFreader::processVal(String data){
	uint32_t dataInt = 0;
	if(currentTag.equals(TAG_NONE) == true) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true ){
		char *p;
		data = data.substring(1);
		uint32_t n = strtoul(data.c_str(), &p, 16);
		if ( * p != 0 ) { //my bad edit was here
		#ifdef DDFREADER_DEBUG
			Serial.println("not a number");
		#endif
		}
		colorArray[deviceInfo.singlecolorCount-1].color = n;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\t\tval: %lu (%u.%u.%u\n",colorArray[deviceInfo.singlecolorCount-1].color, colorArray[deviceInfo.singlecolorCount-1].colorR, colorArray[deviceInfo.singlecolorCount-1].colorG, colorArray[deviceInfo.singlecolorCount-1].colorB);
		#endif
	}
}

void DDFreader::processCaption(String data){

	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1 ){
		colorArray[deviceInfo.singlecolorCount-1].caption = data;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\t\tcaption: %s\n",colorArray[deviceInfo.singlecolorCount-1].caption.c_str());
		#endif
	}
}

void DDFreader::processMindmx(String data){
	int dataInt = 0;
	uint8_t dataUint = 0;

	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1 ){
		dataUint = (uint8_t) data.toInt();
		colorArray[deviceInfo.singlecolorCount-1].mindmx = dataUint;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\t\tmindmx: %i\n",colorArray[deviceInfo.singlecolorCount-1].mindmx);
		#endif

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_cwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW mindmx: %u\n",colorwheel.rainbow_cwMindmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_ccwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW mindmx: %u\n",colorwheel.rainbow_ccwMindmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_ccwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP mindmx: %u\n",colorwheel.rainbow_ccwMindmx);
			#endif

		}

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheel.rainbow_stopMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP mindmx: %i\n",colorwheel.rainbow_stopMindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheel.rainbow_cwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW mindmx: %i\n",colorArray[deviceInfo.singlecolorCount-1].mindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheel.rainbow_ccwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW mindmx %i\n",colorwheel.rainbow_ccwMindmx);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheel.random_fastMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast mindmx: %i\n",colorwheel.random_fastMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheel.random_mediumMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium mindmx: %i\n",colorwheel.random_mediumMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheel.random_slowMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow mindmx %i\n",colorwheel.random_slowMindmx);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_STROBE_RANGE) == true ){	//strobe range
		if(currentCurvetype.equals(STROBETYPE_LINEAR) == true){
			dataInt = (int) data.toInt();
			strobe.linear_exist = true;
			strobe.linear_mindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tlinear mindmx %i\n",strobe.linear_mindmx);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_PULSE) == true){
			dataInt = (int) data.toInt();
			strobe.pulse_exist = true;
			strobe.pulse_mindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tpulse mindmx %i\n",strobe.pulse_mindmx);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_RANDOM) == true){
			dataInt = (int) data.toInt();
			strobe.random_exist = true;
			strobe.random_mindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom mindmx %i\n",strobe.random_mindmx);
			#endif
		}
	}
}

void DDFreader::processMaxdmx(String data){
	int dataInt = 0;
	uint8_t dataUint = 0;

	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1){
		dataUint = (uint8_t) data.toInt();
		colorArray[deviceInfo.singlecolorCount-1].maxdmx = dataUint;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\t\tmaxdmx: %i\n",colorArray[deviceInfo.singlecolorCount-1].maxdmx);
		#endif

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_cwMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW maxdmx: %u\n",colorwheel.rainbow_cwMaxdmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_ccwMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW maxdmx: %u\n",colorwheel.rainbow_ccwMaxdmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbow_stopMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP maxdmx: %u\n",colorwheel.rainbow_stopMaxdmx);
			#endif
			
		}

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheel.rainbow_stopMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP maxdmx: %i\n",colorwheel.rainbow_stopMaxdmx);
			#endif

		}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){
			if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheel.rainbow_cwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CW maxdmx: %i\n",colorwheel.rainbow_cwMaxdmx);
				#endif

			}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheel.rainbow_ccwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CCW maxdmx: %i\n",colorwheel.rainbow_ccwMaxdmx);
				#endif

			}
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheel.random_fastMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast maxdmx: %i\n",colorwheel.random_fastMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheel.random_mediumMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium maxdmx: %i\n",colorwheel.random_mediumMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheel.random_slowMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow maxdmx %i\n",colorwheel.random_slowMaxdmx);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_STROBE_RANGE) == true ){	//strobe range
		if(currentCurvetype.equals(STROBETYPE_LINEAR) == true){
			dataInt = (int) data.toInt();
			strobe.linear_exist = true;
			strobe.linear_maxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tlinear maxdmx %i\n",strobe.linear_maxdmx);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_PULSE) == true){
			dataInt = (int) data.toInt();
			strobe.pulse_exist = true;
			strobe.pulse_maxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tpulse maxdmx %i\n",strobe.pulse_maxdmx);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_RANDOM) == true){
			dataInt = (int) data.toInt();
			strobe.random_exist = true;
			strobe.random_maxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom maxdmx %i\n",strobe.random_maxdmx);
			#endif
		}
	}
}

void DDFreader::processMinval(String data){
	double dataDouble = 0;
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){	//colorwheel rainbow range
		if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbow_cwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW minval: %lf\n",colorwheel.rainbow_cwMinvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbow_ccwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW minval: %lf\n",colorwheel.rainbow_ccwMinvalue);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbow_cwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW minvalue: %lf\n",colorwheel.rainbow_cwMinvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbow_ccwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW minvalue: %lf\n",colorwheel.rainbow_ccwMinvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataDouble = data.toDouble();
			colorwheel.rainbow_stopMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP minvalue: %lf\n",colorwheel.rainbow_stopMinvalue);
			#endif
			
		}

	}else if(currentTag.equals(TAG_FUNCTIONS_STROBE_RANGE) == true ){	//strobe range
		if(currentCurvetype.equals(STROBETYPE_LINEAR) == true){
			dataDouble = data.toDouble();
			strobe.linear_exist = true;
			strobe.linear_minval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tlinar minvalue: %lf\n",strobe.linear_minval);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_PULSE) == true){
			dataDouble = data.toDouble();
			strobe.pulse_exist = true;
			strobe.pulse_minval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tpulse minvalue: %lf\n",strobe.pulse_minval);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_RANDOM) == true){
			dataDouble = data.toDouble();
			strobe.random_exist = true;
			strobe.random_minval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom minvalue: %lf\n",strobe.random_minval);
			#endif
		}
	}
}

void DDFreader::processMaxval(String data){
	double dataDouble = 0;
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){	//colorwheel rainbow range
		if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbow_cwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW maxval: %u\n",colorwheel.rainbow_cwMaxvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbow_ccwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW maxval: %u\n",colorwheel.rainbow_ccwMaxvalue);
			#endif
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbow_cwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW maxvalue: %lf\n",colorwheel.rainbow_cwMaxvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbow_ccwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW maxvalue: %lf\n",colorwheel.rainbow_ccwMaxvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataDouble = data.toDouble();
			colorwheel.rainbow_stopMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP maxvalue: %lf\n",colorwheel.rainbow_stopMaxvalue);
			#endif
			
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_STROBE_RANGE) == true ){	//strobe range
		if(currentCurvetype.equals(STROBETYPE_LINEAR) == true){
			dataDouble = data.toDouble();
			strobe.linear_exist = true;
			strobe.linear_maxval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tlinar maxvalue: %lf\n",strobe.linear_maxval);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_PULSE) == true){
			dataDouble = data.toDouble();
			strobe.pulse_exist = true;
			strobe.pulse_maxval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\tpulse maxvalue: %lf\n",strobe.pulse_maxval);
			#endif
		}else if(currentCurvetype.equals(STROBETYPE_RANDOM) == true){
			dataDouble = data.toDouble();
			strobe.random_exist = true;
			strobe.random_maxval = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom maxvalue: %lf\n",strobe.random_maxval);
			#endif
		}
	}
}
