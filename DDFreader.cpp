/*
 * DDFreader.cpp
 *
 *  Created on: 30 Oct 2022
 *      Author: Chris
 */

#include "DDFreader.h"

TinyXML *DDFreader::xml;
String DDFreader:: _ddfPath = "/";	//init path: root
String DDFreader::currentTag;	//init: type=none
String DDFreader::currentRainbowtype;
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
	uint16_t charCounter = 0;
	uint16_t fileSize = file.size();
	Serial.println("Read from file: ");
	if(fileSize <= DDFBUFSIZE){
	char xmlBuffer[fileSize];
	while(file.available()){
		xmlBuffer[charCounter] =  file.read();
		Serial.print(xmlBuffer[charCounter]);
		charCounter++;
	}
	file.close();

	char *c = xmlBuffer;
	do {
		xml->processChar(*c);
	}  while (*c++);

	}else Serial.println("fille too big! (6000 bytes max)");
}

void DDFreader::XMLcallback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen )
{
  if (statusflags & STATUS_START_TAG)
  {
    if ( tagNameLen )
    {
      Serial.print("Start tag ");
      Serial.println(tagName);

		startTag(String(tagName));
    }
  }
  else if  (statusflags & STATUS_END_TAG)
  {
    Serial.print("End tag ");
    Serial.println(tagName);
	 Serial.println(" ");
  }
  else if  (statusflags & STATUS_TAG_TEXT)
  {
    Serial.print("Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
	 tag(tagName, data);
  }
  else if  (statusflags & STATUS_ATTR_TEXT)
  {
    Serial.print("Attribute:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);

	 attribute(String(tagName), String(data));
  }
  else if  (statusflags & STATUS_ERROR)
  {
    Serial.print("XML Parsing error  Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
}

void DDFreader::startTag(String tagName){
	if(tagName.startsWith(TAG_DEVICE) == 0)Serial.println("xml is not a device");return;	//return if xml is not a device

	
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL) > 0){	//start new colorwheel
		deviceInfo.colorwheelCount++;
		colorwheel_t* newColorwheel = new colorwheel_t[deviceInfo.colorwheelCount];	//declare new array
		std::copy(colorwheelArray, colorwheelArray + std::min(deviceInfo.colorwheelCount-1, deviceInfo.colorwheelCount), newColorwheel);	//copy to new array
		delete[] colorwheelArray;	//delte old array
		colorwheelArray = newColorwheel;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Colorwheel (#%u):\n",deviceInfo.colorwheelCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) > 0){
		currentTag = tagName;
	}else if(tagName.startsWith(TAG_FUNCTIONS_COLORWHEEL_RAINBOW) > 0){
		currentTag = tagName;
	}else if(tagName.startsWith(TAG_FUNCTIONS_COLORWHEEL_RANDOM) > 0){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_DIMMER) > 0){
		deviceInfo.dimmerCount++;
		DDFdimmer* newDimmer = new DDFdimmer[deviceInfo.dimmerCount];	//declare new array
		std::copy(dimmerArray, dimmerArray + std::min(deviceInfo.dimmerCount-1, deviceInfo.dimmerCount), newDimmer);	//copy to new array
		delete[] dimmerArray;	//delte old array
		dimmerArray = newDimmer;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Dimmer (#%u):\n",deviceInfo.dimmerCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_FOCUS) > 0){
		deviceInfo.focusCount++;
		DDFfocus* newFocus = new DDFfocus[deviceInfo.focusCount];	//declare new array
		std::copy(focusArray, focusArray + std::min(deviceInfo.focusCount-1, deviceInfo.focusCount), newFocus);	//copy to new array
		delete[] focusArray;	//delte old array
		focusArray = newFocus;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Focus (#%u):\n",deviceInfo.focusCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_FROST) > 0){
		deviceInfo.frostCount++;
		DDFfrost* newFrost = new DDFfrost[deviceInfo.frostCount];	//declare new array
		std::copy(frostArray, frostArray + std::min(deviceInfo.frostCount-1, deviceInfo.frostCount), newFrost);	//copy to new array
		delete[] frostArray;	//delte old array
		frostArray = newFrost;	//copy to old array
		currentTag = tagName;

	}else if(tagName.equals(TAG_FUNCTIONS_GOBOWHEEL) > 0){
		deviceInfo.gobowheelCount++;
		// DDFgobowheel* newFrost = new DDFfrost[deviceInfo.frostCount];	//declare new array
		// std::copy(frostArray, frostArray + std::min(deviceInfo.frostCount-1, deviceInfo.frostCount), newFrost);	//copy to new array
		// delete[] frostArray;	//delte old array
		// frostArray = newFrost;	//copy to old array
		Serial.printf("new gobowheel (noch nicht implementiert) (#%u):\n",deviceInfo.focusCount-1);
		currentTag = tagName;

	}else if(tagName.equals(TAG_FUNCTIONS_MATRIX) > 0){
		deviceInfo.matrixCount++;
		DDFmatrix* newMatrix = new DDFmatrix[deviceInfo.matrixCount];	//declare new array
		std::copy(matrixArray, matrixArray + std::min(deviceInfo.matrixCount-1, deviceInfo.matrixCount), newMatrix);	//copy to new array
		delete[] matrixArray;	//delte old array
		matrixArray = newMatrix;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Matrix (#%u):\n",deviceInfo.matrixCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_POSITION) > 0){
		deviceInfo.positionCount++;
		DDFposition* newPosition = new DDFposition[deviceInfo.positionCount];	//declare new array
		std::copy(positionArray, positionArray + std::min(deviceInfo.positionCount-1, deviceInfo.positionCount), newPosition);	//copy to new array
		delete[] positionArray;	//delte old array
		positionArray = newPosition;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Position (#%u):\n",deviceInfo.positionCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_POSITION_PAN) > 0){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_POSITION_TILT) > 0){
		currentTag = tagName;
	}else if(tagName.equals(TAG_FUNCTIONS_PRISM) > 0){
		deviceInfo.prismCount++;
		DDFprism* newPrism = new DDFprism[deviceInfo.prismCount];	//declare new array
		std::copy(prismArray, prismArray + std::min(deviceInfo.prismCount-1, deviceInfo.prismCount), newPrism);	//copy to new array
		delete[] prismArray;	//delte old array
		prismArray = newPrism;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Prism (#%u):\n",deviceInfo.prismCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_PTSPEED) > 0){
		deviceInfo.ptspeedCount++;
		DDFptspeed* newPtspeed = new DDFptspeed[deviceInfo.ptspeedCount];	//declare new array
		std::copy(ptspeedArray, ptspeedArray + std::min(deviceInfo.ptspeedCount-1, deviceInfo.ptspeedCount), newPtspeed);	//copy to new array
		delete[] ptspeedArray;	//delte old array
		ptspeedArray = newPtspeed;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Ptspeed (#%u):\n",deviceInfo.ptspeedCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_RAW) > 0){
		deviceInfo.rawCount++;
		DDFraw* newRaw = new DDFraw[deviceInfo.rawCount];	//declare new array
		std::copy(rawArray, rawArray + std::min(deviceInfo.rawCount-1, deviceInfo.rawCount), newRaw);	//copy to new array
		delete[] rawArray;	//delte old array
		rawArray = newRaw;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Raw (#%u):\n",deviceInfo.rawCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_RGB) > 0){
		deviceInfo.rgbCount++;
		DDFrgb* newRgb = new DDFrgb[deviceInfo.rgbCount];	//declare new array
		std::copy(rgbArray, rgbArray + std::min(deviceInfo.rgbCount-1, deviceInfo.rgbCount), newRgb);	//copy to new array
		delete[] rgbArray;	//delte old array
		rgbArray = newRgb;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Rgb (#%u):\n",deviceInfo.rgbCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_SHUTTER) > 0){
		deviceInfo.shutterCount++;
		DDFshutter* newShutter = new DDFshutter[deviceInfo.shutterCount];	//declare new array
		std::copy(shutterArray, shutterArray + std::min(deviceInfo.shutterCount-1, deviceInfo.shutterCount), newShutter);	//copy to new array
		delete[] shutterArray;	//delte old array
		shutterArray = newShutter;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Shutter (#%u):\n",deviceInfo.shutterCount-1);

	}else if(tagName.equals(TAG_FUNCTIONS_STEP) > 0){
		deviceInfo.stepCount++;
		DDFstep* newStepfunc = new DDFstep[deviceInfo.stepCount];	//declare new array
		std::copy(stepfuncArray, stepfuncArray + std::min(deviceInfo.stepCount-1, deviceInfo.stepCount), newStepfunc);	//copy to new array
		delete[] stepfuncArray;	//delte old array
		stepfuncArray = newStepfunc;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Step (#%u):\n",deviceInfo.stepCount-1);


	}else if(tagName.equals(TAG_FUNCTIONS_ZOOM) > 0){
		deviceInfo.zoomCount++;
		DDFzoom* newZoom = new DDFzoom[deviceInfo.zoomCount];	//declare new array
		std::copy(zoomArray, zoomArray + std::min(deviceInfo.zoomCount-1, deviceInfo.zoomCount), newZoom);	//copy to new array
		delete[] zoomArray;	//delte old array
		zoomArray = newZoom;	//copy to old array
		currentTag = tagName;
		Serial.printf("new Zoom (#%u):\n",deviceInfo.zoomCount-1);
	}
}

void DDFreader::tag(String tagName, String data){
	if(tagName.equals(TAG_INFO_LIBID) > 0){	//devicetype
		ddfInfo.ddfLibraryId = (int) data.toInt();
	}else if(tagName.equals(TAG_INFO_MODEL) > 0){
		ddfInfo.model = data;
	}else if(tagName.equals(TAG_INFO_VENDOR) > 0){
		ddfInfo.vendor = data;
	}else if(tagName.equals(TAG_INFO_AUTHOR) > 0){
		ddfInfo.author = data;
	}else if(tagName.equals(TAG_INFO_MODE) > 0){
		ddfInfo.mode = data;
	}
}

void DDFreader::attribute(String tagName, String data){
	if(tagName.equals(ATTRIBUTE_DEVICETYPE) > 0){	//devicetype
		if(data.equals("DMXDevice") > 0) Serial.println("type: DMXdevice");
	}else if(tagName.equals(ATTRIBUTE_DMXCVERSION) > 0){	//dmxcversion
		String _mainversion = data.substring(0,data.indexOf("."));
		Serial.print("\tmainversion: ");Serial.println(_mainversion);
		ddfInfo.dmxcversion[0] = (int) _mainversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		String _subversion = data.substring(0,data.indexOf("."));
		Serial.print("\tsubversion: ");Serial.println(_subversion);
		ddfInfo.dmxcversion[1] = (int) _subversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		Serial.print("\tsubsubversion: ");Serial.println(data);
		ddfInfo.dmxcversion[2] = (int) data.toInt();

	}else if(tagName.equals(ATTRIBUTE_DDFVERSION) > 0){	//ddfversion
		String _mainversion = data.substring(0,data.indexOf("."));
		Serial.print("\tmainversion: ");Serial.println(_mainversion);
		ddfInfo.ddfversion[0] = (int) _mainversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		String _subversion = data.substring(0,data.indexOf("."));
		Serial.print("\tsubversion: ");Serial.println(_subversion);
		ddfInfo.ddfversion[1] = (int) _subversion.toInt();
		data = data.substring(data.indexOf(".")+1, data.length());
		Serial.print("\tsubsubversion: ");Serial.println(data);
		ddfInfo.ddfversion[2] = (int) data.toInt();


	}else if(tagName.equals(ATTRIBUTE_DMXCHANNEL) > 0){	//attribute "dmxchannel"
		processDmxchannel(data);
	}else if(tagName.equals(ATTRIBUTE_FINEDMXCHANNEL) > 0){	//attribute "finedmxchannel"
		processFinedmx(data);
	}else if(tagName.equals(ATTRIBUTE_RANGE) > 0){	//attribute "range"
		processRange(data);
	}else if(tagName.equals(ATTRIBUTE_TYPE) > 0){	//attribute "type"
		processType(data);
	}
}

void DDFreader::processDmxchannel(String data){
	int dataInt = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_COLORWHEEL ){
		dataInt = (int) data.toInt();
		colorwheelArray[deviceInfo.colorwheelCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",colorwheelArray[deviceInfo.colorwheelCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_DIMMER ){
		dataInt = (int) data.toInt();
		dimmerArray[deviceInfo.dimmerCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",dimmerArray[deviceInfo.dimmerCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_FOCUS ){
		dataInt = (int) data.toInt();
		focusArray[deviceInfo.focusCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",focusArray[deviceInfo.focusCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_FROST ){
		dataInt = (int) data.toInt();
		frostArray[deviceInfo.frostCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",frostArray[deviceInfo.frostCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL ){
		dataInt = (int) data.toInt();
		gobowheelArray[deviceInfo.gobowheelCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",gobowheelArray[deviceInfo.gobowheelCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].pan_dmxchannel = dataInt;
		Serial.printf("\npan dmxchannel: (#%u):\n",positionArray[deviceInfo.positionCount-1].pan_dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].tilt_dmxchannel = dataInt;
		Serial.printf("\n tilt dmxchannel: (#%u):\n",positionArray[deviceInfo.positionCount-1].tilt_dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_PRISM ){
		dataInt = (int) data.toInt();
		prismArray[deviceInfo.prismCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",prismArray[deviceInfo.prismCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_PTSPEED ){
		dataInt = (int) data.toInt();
		ptspeedArray[deviceInfo.ptspeedCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",ptspeedArray[deviceInfo.ptspeedCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RAW ){
		dataInt = (int) data.toInt();
		rawArray[deviceInfo.rawCount-1].dmxchannel = dataInt;
		Serial.printf("\ndmxchannel: (#%u):\n",rawArray[deviceInfo.rawCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_R ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].redDmxchannel = dataInt;
		Serial.printf("\nR dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].redDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_G ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].greenDmxchannel = dataInt;
		Serial.printf("\nG dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].greenDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_B ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].blueDmxchannel = dataInt;
		Serial.printf("\nB dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].blueDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_W ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel = dataInt;
		Serial.printf("\nW dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_A ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].amberDmxchannel = dataInt;
		Serial.printf("\nA dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].amberDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_RGB_U ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].uvDmxchannel = dataInt;
		Serial.printf("\nU dmxchannel: (#%u):\n",rgbArray[deviceInfo.rgbCount-1].uvDmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_SHUTTER ){
		dataInt = (int) data.toInt();
		shutterArray[deviceInfo.shutterCount-1].dmxchannel = dataInt;
		Serial.printf("\nA dmxchannel: (#%u):\n",shutterArray[deviceInfo.shutterCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_STEP ){
		dataInt = (int) data.toInt();
		stepfuncArray[deviceInfo.stepCount-1].dmxchannel = dataInt;
		Serial.printf("\nA dmxchannel: (#%u):\n",stepfuncArray[deviceInfo.stepCount-1].dmxchannel);

	}else if(currentTag == TAG_FUNCTIONS_ZOOM ){
		dataInt = (int) data.toInt();
		zoomArray[deviceInfo.zoomCount-1].dmxchannel = dataInt;
		Serial.printf("\nA dmxchannel: (#%u):\n",zoomArray[deviceInfo.zoomCount-1].dmxchannel);
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
	}else if(currentTag == TAG_FUNCTIONS_FOCUS ){
		dataInt = (int) data.toInt();
		focusArray[deviceInfo.focusCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_FROST ){
		dataInt = (int) data.toInt();
		frostArray[deviceInfo.frostCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL ){
		//do nothing (no finedmx for gobowheels)
	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].pan_finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT ){
		dataInt = (int) data.toInt();
		positionArray[deviceInfo.positionCount-1].tilt_finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_PRISM ){
		dataInt = (int) data.toInt();
		prismArray[deviceInfo.prismCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_PTSPEED ){
		dataInt = (int) data.toInt();
		ptspeedArray[deviceInfo.ptspeedCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RAW ){
		dataInt = (int) data.toInt();
		rawArray[deviceInfo.rawCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_R ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].redDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_G ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].greenDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_B ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].blueDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_W ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].whiteDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_A ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].amberDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_RGB_U ){
		dataInt = (int) data.toInt();
		rgbArray[deviceInfo.rgbCount-1].uvDmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_SHUTTER ){
		dataInt = (int) data.toInt();
		shutterArray[deviceInfo.shutterCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_STEP ){
		dataInt = (int) data.toInt();
		stepfuncArray[deviceInfo.stepCount-1].finedmxchannel = dataInt;
	}else if(currentTag == TAG_FUNCTIONS_ZOOM ){
		dataInt = (int) data.toInt();
		zoomArray[deviceInfo.zoomCount-1].finedmxchannel = dataInt;
	}
}

void DDFreader::processRange(String data){	//attribute "range"
	int dataInt = 0;
	double dataDouble = 0;

	if(currentTag == TAG_NONE) return;
	else if(currentTag == TAG_FUNCTIONS_GOBOWHEEL_INDEX_RANGE ){
		dataDouble = (double) data.toDouble();
		gobowheelArray[deviceInfo.gobowheelCount-1].indexRange = dataDouble;
	}else if(currentTag == TAG_FUNCTIONS_POSITION_PAN_RANGE ){
		dataDouble = (double) data.toDouble();
		positionArray[deviceInfo.positionCount-1].pan_range = dataDouble;
	}else if(currentTag == TAG_FUNCTIONS_POSITION_TILT_RANGE ){
		dataDouble = (double) data.toDouble();
		positionArray[deviceInfo.positionCount-1].tilt_range = dataDouble;
	}
}

void DDfreader::processType(String data){	//process attribute "type"

	if(currentTag == TAG_FUNCTIONS_COLORWHEEL_STEP){	//colorwheel step
		if(data == STEPTYPE_COLOR){	//if type is "color": increase singlecolor array
			deviceInfo.singlecolorCount++;
			singlecolor_t* newSinglecolor = new singlecolor_t[deviceInfo.singlecolorCount];	//declare new array
			std::copy(colorArray, colorArray + std::min(deviceInfo.singlecolorCount-1, deviceInfo.singlecolorCount), newSinglecolor);	//copy to new array
			delete[] colorArray;	//delte old array
			colorArray = newSinglecolor;	//copy to old array
		}
	}else if(currentTag == TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP){	//colorwheel rainbow step
		if(data == ROTATIONTYPE_STOP){
			currentRainbowtype = ROTATIONTYPE_STOP;
		}
	}else if(currentTag == TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE){	//colorwheel rainbow range
		if(data == ROTATIONTYPE_CLOCKWISE){	//cw
			currentRainbowtype = ROTATIONTYPE_STOP;
		}else if(data == ROTATIONTYPE_COUNTERCLOCKWISE){	//ccw
			currentRainbowtype = ROTATIONTYPE_COUNTERCLOCKWISE;
		}
	}

}

void DDFreader::processVal(String data){
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1 ){
		dataInt = (uint32_t) data.toInt();
		colorArray[deviceInfo.singlecolorCount-1].color = dataInt;
	}
}

void DDFreader::processCaption(String data){
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1 ){
		colorArray[deviceInfo.singlecolorCount-1].caption = data;
	}
}

void DDFreader::processMindmx(String data){
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1 ){
		dataInt = (uint8_t) data.toInt();
		colorArray[deviceInfo.singlecolorCount-1].mindmx = dataInt;

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.eguals(ROTATIONTYPE_STOP) == 1){
			dataInt = (uint8_t) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMindmx = dataInt;

		}else if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataInt = (uint8_t) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMindmx = dataInt;

		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataInt = (uint8_t) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMindmx = dataInt;

		}
	}
}

void DDFreader::processMaxdmx(String data){
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTagequals(TAG_FUNCTIONS_COLORWHEEL_STEP) == 1){
		dataInt = (uint8_t) data.toInt();
		colorArray[deviceInfo.singlecolorCount-1].maxdmx = dataInt;

	}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP) == 1){
		if(currentRainbowtype.eguals(ROTATIONTYPE_STOP) == 1){
			dataInt = (uint8_t) data.toInt();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowStopMaxdmx = dataInt;

		}else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){
			if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
				dataInt = (uint8_t) data.toInt();
				colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMaxdmx = dataInt;

			}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
				dataInt = (uint8_t) data.toInt();
				colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMaxdmx = dataInt;

			}
		}
		
		

	}
}

void DDFreader::processMinval(String data){
	double dataDouble = 0;
	if(currentTag.equals(TAG_NONE) == 1) return;
	else if(currentTag.equals(TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE) == 1){	//colorwheel rainbow range
		if(currentRainbowtype.equals(ROTATIONTYPE_CLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCwMinval = dataDouble;
		}else if(currentRainbowtype.equals(ROTATIONTYPE_COUNTERCLOCKWISE) ==  1){
			dataDouble = (double) data.toDouble();
			colorwheelArray[deviceInfo.colorwheelCount-1].rainbowCCwMinval = dataDouble;

		}
	}
}

void DDFreader::endTag(String tagName){
	if(tagName.equals(TAG_FUNCTIONS_COLORWHEEL_STEP) > 0){
		currentTag = TAG_NONE;
	}
}