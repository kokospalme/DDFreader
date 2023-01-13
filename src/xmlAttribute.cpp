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
			colorwheel.rainbowCwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW mindmx: %u\n",colorwheel.rainbowCwMindmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbowCCwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW mindmx: %u\n",colorwheel.rainbowCCwMindmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbowCCwMindmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP mindmx: %u\n",colorwheel.rainbowCCwMindmx);
			#endif

		}

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheel.rainbowStopMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP mindmx: %i\n",colorwheel.rainbowStopMindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheel.rainbowCwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW mindmx: %i\n",colorArray[deviceInfo.singlecolorCount-1].mindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheel.rainbowCCwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW mindmx %i\n",colorwheel.rainbowCCwMindmx);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheel.randomFastMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast mindmx: %i\n",colorwheel.randomFastMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheel.randomMediumMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium mindmx: %i\n",colorwheel.randomMediumMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheel.randomSlowMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow mindmx %i\n",colorwheel.randomSlowMindmx);
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
			colorwheel.rainbowCwMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW maxdmx: %u\n",colorwheel.rainbowCwMaxdmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbowCCwMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW maxdmx: %u\n",colorwheel.rainbowCCwMaxdmx);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataUint = (uint8_t) data.toInt();
			colorwheel.rainbowStopMaxdmx = dataUint;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP maxdmx: %u\n",colorwheel.rainbowStopMaxdmx);
			#endif
			
		}

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheel.rainbowStopMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP maxdmx: %i\n",colorwheel.rainbowStopMaxdmx);
			#endif

		}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){
			if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheel.rainbowCwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CW maxdmx: %i\n",colorwheel.rainbowCwMaxdmx);
				#endif

			}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheel.rainbowCCwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CCW maxdmx: %i\n",colorwheel.rainbowCCwMaxdmx);
				#endif

			}
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheel.randomFastMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast maxdmx: %i\n",colorwheel.randomFastMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheel.randomMediumMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium maxdmx: %i\n",colorwheel.randomMediumMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheel.randomSlowMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow maxdmx %i\n",colorwheel.randomSlowMaxdmx);
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
			colorwheel.rainbowCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW minval: %lf\n",colorwheel.rainbowCwMinvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbowCCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW minval: %lf\n",colorwheel.rainbowCCwMinvalue);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbowCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW minvalue: %lf\n",colorwheel.rainbowCwMinvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbowCCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW minvalue: %lf\n",colorwheel.rainbowCCwMinvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataDouble = data.toDouble();
			colorwheel.rainbowStopMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP minvalue: %lf\n",colorwheel.rainbowStopMinvalue);
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
			colorwheel.rainbowCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW maxval: %u\n",colorwheel.rainbowCwMaxvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheel.rainbowCCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW maxval: %u\n",colorwheel.rainbowCCwMaxvalue);
			#endif
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE) == 1 ){
		if(currentRotationtype == ROTATIONTYPE_CLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbowCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CW maxvalue: %lf\n",colorwheel.rainbowCwMaxvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_COUNTERCLOCKWISE){
			dataDouble = data.toDouble();
			colorwheel.rainbowCCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation CCW maxvalue: %lf\n",colorwheel.rainbowCCwMaxvalue);
			#endif

		}else if(currentRotationtype == ROTATIONTYPE_STOP){
			dataDouble = data.toDouble();
			colorwheel.rainbowStopMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\twheelrotation STOP maxvalue: %lf\n",colorwheel.rainbowStopMaxvalue);
			#endif
			
		}
	}
}
