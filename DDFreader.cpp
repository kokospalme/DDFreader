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
String DDFreader::currentRotationtype;
String DDFreader::currentRainbowtype;
String DDFreader::currentRandomtype;
ddfInformation_t DDFreader::ddfInfo;
deviceInformation_t DDFreader::deviceInfo;

colorwheel_t DDFreader::colorwheel;	//temp colorwheel stuff
singlecolor_t* DDFreader::colorArray;
DDFcolorwheel* DDFreader::colorwheelArray;
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
			xml->softreset();
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

		#ifdef DDFREADER_DEBUG_CALLBACK
      Serial.print("Start tag ");
      Serial.println(tagName);
		#endif

		startTag(String(tagName));
		
  }else if(statusflags & STATUS_END_TAG){	//process end tag

		#ifdef DDFREADER_DEBUG_CALLBACK
		Serial.print("End tag ");
		Serial.println(tagName);
		#endif

		endTag(String(tagName));

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
		#ifdef DDFREADER_DEBUG_CALLBACK
		Serial.print("XML Parsing error  Tag:");
		Serial.print(tagName);
		Serial.print(" text:");
		Serial.println(data);
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
	}else if(tagName.equals(ATTRIBUTE_VAL) == true){	//attribute "val"
		processVal(data);
	}else if(tagName.equals(ATTRIBUTE_MINDMX) == true){	//attribute "mindmx"
		processMindmx(data);
	}else if(tagName.equals(ATTRIBUTE_MAXDMX) == true){	//attribute "maxdmx"
		processMaxdmx(data);
	}else if(tagName.equals(ATTRIBUTE_MINVAL) == true){	//attribute "minval"
		processMinval(data);
	}else if(tagName.equals(ATTRIBUTE_MAXVAL) == true){	//attribute "maxval"
		processMaxval(data);
	}else if(tagName.equals(ATTRIBUTE_CAPTION) == true){	//attribute "caption"
		processCaption(data);
	}
}

void DDFreader::endTag(String tagName){
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == true){	//update colorCount in colorwheel
		currentTag = TAG_NONE;
	}else	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL) == true){	//end colorwheel
		colorwheel.size = (uint16_t) deviceInfo.singlecolorCount;
		colorwheel.wheelNo = deviceInfo.colorwheelCount-1;
		colorwheelArray[deviceInfo.colorwheelCount-1].set(colorwheel);	//current colorwheel to wheel
		colorwheelArray[deviceInfo.colorwheelCount-1].setColors(colorArray);	//colors to wheel
		
		delete[] colorArray;	//delete single colors
		colorwheel_t _empty;
		colorwheel = _empty;	//reset colorwheel
		deviceInfo.singlecolorCount = 0;	//reset singlecolorCount;
		currentTag = TAG_NONE;
		#ifdef DDFREADER_DEBUG
		Serial.printf(">> colorwheel #%u written to DDFdevice (%u colors) \n",
		colorwheelArray[deviceInfo.colorwheelCount-1].get().wheelNo,
		colorwheelArray[deviceInfo.colorwheelCount-1].get().size);
		#endif
	}
}