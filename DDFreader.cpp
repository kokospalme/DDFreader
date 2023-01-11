/*
 * DDFreader.cpp
 *
 *  Created on: 30 Oct 2022
 *      Author: Chris
 * 
 * https://forum.arduino.cc/t/correct-way-to-dynamically-resize-an-array-using-new-and-delete/508315
 * 
 */

#include "DDFreader.h"

TinyXML *DDFreader::xml;
String DDFreader:: _ddfPath = "/";	//init path: root
String DDFreader::parentTag = "/device";
String DDFreader::lastTag= "";
String DDFreader::currentTag;	//init: type=none
String DDFreader::currentRainbowtype;
String DDFreader::currentRandomtype;
ddfInformation_t DDFreader::ddfInfo;
deviceInformation_t DDFreader::deviceInfo;

colorwheel_t* DDFreader::colorwheelArray;	//temp array
singlecolor_t* DDFreader::colorArray;
DDFdimmer* DDFreader::dimmerArray;
DDFfocus* DDFreader::focusArray;
DDFfrost* DDFreader::frostArray;
gobowheel_t* DDFreader::gobowheelArray;
singlegobo_t* DDFreader::goboArray;
DDFmatrix* DDFreader::matrixArray;
DDFposition* DDFreader::positionArray;
DDFprism* DDFreader::prismArray;
DDFptspeed* DDFreader::ptspeedArray;
DDFraw* DDFreader::rawArray;
DDFrgb* DDFreader::rgbArray;
DDFshutter* DDFreader::shutterArray;
DDFstep* DDFreader::stepfuncArray;
singlestep_t* DDFreader::stepArray;
DDFzoom* DDFreader::zoomArray;

DDFreader::DDFreader(TinyXML *xml){	//class constructor
	this->xml = xml;
}

void DDFreader::init(){
	Serial.println("initialize SD card...");

	if(!SD.begin(PIN_SPI_CSSD)){
		Serial.println("Card Mount Failed");
		return;
	}
	uint8_t cardType = SD.cardType();

	if(cardType == CARD_NONE){
		Serial.println("No SD card attached");
		return;
	}

	Serial.print("SD Card Type: ");
	if(cardType == CARD_MMC){
		Serial.println("MMC");
	} else if(cardType == CARD_SD){
		Serial.println("SDSC");
	} else if(cardType == CARD_SDHC){
		Serial.println("SDHC");
	} else {
		Serial.println("UNKNOWN");
	}

	uint64_t cardSize = SD.cardSize() / (1024 * 1024);
	Serial.printf("SD Card Size: %llu MB\n", cardSize);
}

void DDFreader::setDDFpath(String path){
	if(path.endsWith("/"))_ddfPath = path;
	else path+="/";_ddfPath = path;	//add "/" if missing
}

void DDFreader::readDDF(String filename){
	String path = _ddfPath;
	path += filename;
	Serial.printf("Reading file: %s\n", path.c_str());

	File file = SD.open(path.c_str());	//open file


	if(!file){
		Serial.println("Failed to open file for reading");
		return;
	}

//filesize OK --> read charwise
	uint32_t charCounter = 0;	//overall counter (für file.read())
	uint32_t charCountBuffer = 0;
	uint32_t fallbackChar = 0;
	bool _fileread = false;
	uint16_t fileSize = file.size();
	Serial.println("Read from file: ");
	char _buf[DDFBUFSIZE];
	char xmlBuffer[DDFBUFSIZE];
	
	while(file.available()){

		xmlBuffer[charCounter] =  file.read();	//read char from file
		#ifdef DDFREADER_DEBUG_XML
		Serial.print(xmlBuffer[charCounter]);
		#endif

		if(xmlBuffer[charCounter] == '\n' && charCounter >= DDFBUFSIZE - DDFBUFFERSIZE_SAFETY){	//if file reaches end of buffer
			fallbackChar += charCounter;
			// file.close();

			Serial.printf("\n === buffer exceed (with safety).charCounter:%u.Serialize...\n", charCounter);
			// charCounter = 0;	//charCounter to Zero
			char *c = xmlBuffer;	//deserialize xml file	//ToDo: wieder aktivieren
			do {
				xml->processChar(*c);
			}  while (*c++);

			memset(xmlBuffer, 0, sizeof(xmlBuffer));	//clear xml Buffer
			xml->reset();
			// file = SD.open(path.c_str());	//reopen file
			int i = 0;

			while(Serial.available() == false){}
			while(Serial.available()){
				Serial.read();
			}
			charCounter = 0;	//reset charCounter
		}else{
			charCounter++;
		}

	}
	file.close();
	Serial.println("===== FILE CLOSED =====");

	if(_fileread == false){
		char *c = xmlBuffer;
		do {
			// xml->processChar(*c);
		}  while (*c++);
	}
	//file is read
	DDFdevice _device(ddfInfo, deviceInfo);

	DDFcolorwheel _colorwheels[deviceInfo.colorwheelCount];
	for(int i = 0; i < deviceInfo.colorwheelCount; i++){
		uint16_t singleColorPerWheel = 0;
		for(int j = 0; j < deviceInfo.singlecolorCount; j++){
			if(colorArray[j].wheelNo == i) singleColorPerWheel++;
		}
		if(singleColorPerWheel == 0){
			Serial.println("no color to wheel found");
			return;
		}
		singlecolor_t _singlecolorsOnWheel[singleColorPerWheel];	//array for all 
		uint16_t _singlecolorCount = 0;
		for(int j = 0; j < deviceInfo.singlecolorCount; j++){
			if(colorArray[j].wheelNo == i){
				_singlecolorsOnWheel[_singlecolorCount] = colorArray[j];
				Serial.printf("added color #%u on wheel #%u \n", _singlecolorCount, i );
				_singlecolorCount++;
			}
		}
		_colorwheels[i].setColors(colorArray);	//colorarray
	}
	_device.addColorwheels(_colorwheels);


	return;
}

void DDFreader::XMLcallback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen ){
	// Serial.printf("TAG: %s", tagName);

  if (statusflags & STATUS_START_TAG && tagNameLen){	//process start tag

		String _tag = String(tagName);
		String _lastParent = lastTag.substring(0,_tag.lastIndexOf('/'));

		if(_tag.startsWith(_lastParent) == true && _lastParent.length() > 0){	//if tag starts with parent tag: same block
		// Serial.print("= tag OK =");
			lastTag = _tag;
		}else{	// next packet: Tag is incomplete
		// Serial.print("= tag incomplete =");
			_tag = lastTag.substring(0, lastTag.lastIndexOf('/')) + _tag;
			lastTag = _tag;
			_lastParent = lastTag.substring(0,_tag.lastIndexOf('/'));
		}

		#ifdef DDFREADER_DEBUG_CALLBACK
      Serial.print("Start tag ");
      Serial.print(tagName);
		Serial.printf("\tTAG: %s, lastTag: %s,  lastParent:%s\n", _tag, lastTag.c_str(), _lastParent.c_str());
		#endif
		startTag(_tag);
		

  }else if(statusflags & STATUS_END_TAG){	//process end tag


		String _tag = String(tagName);
		String _lastParent = lastTag.substring(0,_tag.lastIndexOf('/'));	

		if(_tag.startsWith(_lastParent) == true && _lastParent.length() > 0){	//if tag starts with parent tag: same block
			
		}else{	// next packet: Tag is incomplete
			_tag = lastTag.substring(0, lastTag.lastIndexOf('/')) + _tag;
			lastTag = _tag;
			_lastParent = lastTag.substring(0,_tag.lastIndexOf('/'));
		}

		#ifdef DDFREADER_DEBUG_CALLBACK
		Serial.print("End tag ");
		Serial.print(tagName);
		Serial.printf("\tTAG: %s, lastTag: %s,  lastParent:%s\n", _tag, lastTag.c_str(), _lastParent.c_str());
		#endif

		endTag(_tag);

  }else if(statusflags & STATUS_TAG_TEXT){	//process tag
		#ifdef DDFREADER_DEBUG_CALLBACK
		Serial.print("Tag:");
		Serial.print(tagName);
		Serial.print(" text:");
		Serial.println(data);
		#endif
		tag(tagName, data);

	}else if(statusflags & STATUS_ATTR_TEXT){ 	//process attribute
		#ifdef DDFREADER_DEBUG_CALLBACK
		Serial.print("Attribute:");
		Serial.print(tagName);
		Serial.print(" text:");
		Serial.println(String(data));
		#endif

		attribute(String(tagName), String(data));

  }else if(statusflags & STATUS_ERROR){	//xml error
		// #ifdef DDFREADER_DEBUG_CALLBACK
		// Serial.print("XML Parsing error  Tag:");
		// Serial.print(tagName);
		// Serial.print(" text:");
		// Serial.println(data);
		// #endif
  }
}


void DDFreader::startTag(String tagName){

	// tagName.trim();
	// Serial.print("Start tag ");
	// Serial.println(tagName);

	if(tagName.startsWith(TAG_DEVICE) == false){
		#ifdef DDFREADER_DEBUG
		Serial.printf("xml is not a device. Tag:%s\n", tagName.c_str());
		#endif
		// return;	//return if xml is not a device
	}
	
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL) == true){	//start new colorwheel
		deviceInfo.colorwheelCount++;
		colorwheel_t* newColorwheel = new colorwheel_t[deviceInfo.colorwheelCount];	//declare new array
		std::copy(colorwheelArray, colorwheelArray + std::min(deviceInfo.colorwheelCount-1, deviceInfo.colorwheelCount), newColorwheel);	//copy to new array
		delete[] colorwheelArray;	//delte old array
		colorwheelArray = newColorwheel;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Colorwheel (#%u):\n",deviceInfo.colorwheelCount-1);
		#endif

	}else if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true){
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
		deviceInfo.gobowheelCount++;
		// DDFgobowheel* newFrost = new DDFfrost[deviceInfo.frostCount];	//declare new array
		// std::copy(frostArray, frostArray + std::min(deviceInfo.frostCount-1, deviceInfo.frostCount), newFrost);	//copy to new array
		// delete[] frostArray;	//delte old array
		// frostArray = newFrost;	//copy to old array
		currentTag = tagName;
		#ifdef DDFREADER_DEBUG
		Serial.printf("new Gobowheel (noch nicht implementiert) (#%u):\n",deviceInfo.focusCount-1);
		#endif
		

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
	}
}

void DDFreader::tag(String tagName, String data){
	if(tagName.equals(TAG_INFO_LIBID) == true){	//devicetype
		ddfInfo.ddfLibraryId = (int) data.toInt();
	}else if(tagName.equals(TAG_INFO_MODEL) == true){
		ddfInfo.model = data;
	}else if(tagName.equals(TAG_INFO_VENDOR) == true){
		ddfInfo.vendor = data;
	}else if(tagName.equals(TAG_INFO_AUTHOR) == true){
		ddfInfo.author = data;
	}else if(tagName.equals(TAG_INFO_MODE) == true){
		ddfInfo.mode = data;
	}
}




void DDFreader::attribute(String tagName, String data){
	// Serial.printf("process attribute. Tag: %s, data: %s\n", tagName.c_str(), data.c_str());

	if(tagName.equals(ATTRIBUTE_DMXCVERSION) == true){	//dmxcversion
		String _mainversion = data.substring(0,data.indexOf("."));
		#ifdef DDFREADER_DEBUG
		Serial.print("\tdmxc mainversion: ");Serial.println(_mainversion);
		#endif
		ddfInfo.dmxcversion[0] = (int) _mainversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		String _subversion = data.substring(0,data.indexOf("."));
		#ifdef DDFREADER_DEBUG
		Serial.print("\tdmxc subversion: ");Serial.println(_subversion);
		#endif
		ddfInfo.dmxcversion[1] = (int) _subversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		#ifdef DDFREADER_DEBUG
		Serial.print("\tdmxc subsubversion: ");Serial.println(data);
		#endif
		ddfInfo.dmxcversion[2] = (int) data.toInt();

	}else if(tagName.equals(ATTRIBUTE_DDFVERSION) == true){	//ddfversion
		String _mainversion = data.substring(0,data.indexOf("."));
		#ifdef DDFREADER_DEBUG
		Serial.print("\tddf mainversion: ");Serial.println(_mainversion);
		#endif
		ddfInfo.ddfversion[0] = (int) _mainversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		String _subversion = data.substring(0,data.indexOf("."));
		#ifdef DDFREADER_DEBUG
		Serial.print("\tddf subversion: ");Serial.println(_subversion);
		#endif
		ddfInfo.ddfversion[1] = (int) _subversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		#ifdef DDFREADER_DEBUG
		Serial.print("\tddf subsubversion: ");Serial.println(data);
		#endif
		ddfInfo.ddfversion[2] = (int) data.toInt();


	}else if(tagName.equals(ATTRIBUTE_DMXCHANNEL) == true){	//attribute "dmxchannel"
		processDmxchannel(data);
	}else if(tagName.equals(ATTRIBUTE_FINEDMXCHANNEL) == true){	//attribute "finedmxchannel"
		processFinedmx(data);
	}else if(tagName.equals(ATTRIBUTE_RANGE) == true){	//attribute "range"
		processRange(data);
	}else if(tagName.equals(ATTRIBUTE_TYPE) == true){	//attribute "type"
		processType(data);
	}else if(tagName.equals(ATTRIBUTE_VAL) == true){	//attribute "type"
		processVal(data);
	}else if(tagName.equals(ATTRIBUTE_MINDMX) == true){	//attribute "type"
		processMindmx(data);
	}else if(tagName.equals(ATTRIBUTE_MAXDMX) == true){	//attribute "type"
		processMaxdmx(data);
	}else if(tagName.equals(ATTRIBUTE_CAPTION) == true){	//attribute "type"
		processCaption(data);
	}
}

void DDFreader::processDmxchannel(String data){
	int dataInt = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_COLORWHEEL ){
		dataInt = (int) data.toInt();
		colorwheelArray[deviceInfo.colorwheelCount-1].dmxchannel = dataInt;
		#ifdef DDFREADER_DEBUG
		Serial.printf("\tdmxchannel: %u\n",colorwheelArray[deviceInfo.colorwheelCount-1].dmxchannel);
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
			delete[] colorArray;	//delte old array
			colorArray = newSinglecolor;	//copy to old array
			colorArray[deviceInfo.singlecolorCount-1].wheelNo = deviceInfo.colorwheelCount-1;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\t==new step(color) (#%u):\n",deviceInfo.singlecolorCount-1);
			#endif

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
		Serial.printf("\t\tval: %lu\n",colorArray[deviceInfo.singlecolorCount-1].color);
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

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP mindmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW mindmx: %i\n",colorArray[deviceInfo.singlecolorCount-1].mindmx);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW mindmx %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMindmx);
			#endif

		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomFastMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast mindmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomFastMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomMediumMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium mindmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomMediumMindmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomSlowMindmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow mindmx %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomSlowMindmx);
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

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.equals(ROTATIONTYPE_STOP) == 1){
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow STOP maxdmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMaxdmx);
			#endif

		}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){
			if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CW maxdmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMaxdmx);
				#endif

			}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
				dataInt = (int) data.toInt();
				colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMaxdmx = dataInt;
				#ifdef DDFREADER_DEBUG
				Serial.printf("\trainbow CCW maxdmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMaxdmx);
				#endif

			}
		}
	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP) == 1){
		if(currentRandomtype.equals(RANDOM_TYPE_FAST) == 1){	//fast
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomFastMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom fast maxdmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomFastMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_MEDIUM) ==  1){	//medium
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomMediumMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom medium maxdmx: %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomMediumMaxdmx);
			#endif

		}else if(currentRainbowtype.equals(RANDOM_TYPE_SLOW) ==  1){	//slow
			dataInt = (int) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].randomSlowMaxdmx = dataInt;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trandom slow maxdmx %i\n",colorwheelArray[deviceInfo.colorwheelCount-1].randomSlowMaxdmx);
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
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW minval: %lf\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMinvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMinvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW minval: %lf\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMinvalue);
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
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CW maxval: %u\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMaxvalue);
			#endif

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMaxvalue = dataDouble;
			#ifdef DDFREADER_DEBUG
			Serial.printf("\trainbow CCW maxval: %u\n",colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMaxvalue);
			#endif
		}
	}
}

void DDFreader::endTag(String tagName){
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true){	//update colorCount in colorwheel
		currentTag = TAG_NONE;
	}else	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL) == true){	//end colorwheel
		colorwheelArray[deviceInfo.colorwheelCount-1].size = (uint16_t) deviceInfo.singlecolorCount;
		currentTag = TAG_NONE;
	}
}