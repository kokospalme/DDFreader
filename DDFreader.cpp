/*
 * DDFreader.cpp
 *
 *  Created on: 30 Oct 2022
 *      Author: Chris
 */

#include "DDFreader.h"




//void DDFreader::readDDF(){
//
//	getDDFInformation();	//read DDF information
//	getDDFfuncDimmer();
//	getDDFfuncPosition();
//	getDDFfuncPtspeed();
//	getDDFfuncRgb();
//}
DDFreader::DDFreader(){
	device = new DDFdevice;

	dimmerArray = new DDFdimmer [1];	//initialize functionArrays
	rgbArray = new DDFrgb [1];
}

void DDFreader::setDDFpath(String path){
	_ddfPath = path;
}

void DDFreader::checkFunctions(String filename){
    String path = _ddfPath;
    String _filename = filename;
    path +=_filename;
    Serial.printf("Reading file: %s\n", path.c_str());

//    const char* pathStr = path.c_str();

    File file = SD.open(path.c_str());


    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("Read from file: ");
    uint16_t charCounter = 0;
    uint16_t fileSize = file.size();

    if(fileSize <= 6000){
    	char jsonBuffer[fileSize];

        while(file.available()){
        	jsonBuffer[charCounter] =  file.read();

//        	Serial.print(jsonBuffer[charCounter]);
        	charCounter++;
        }
        file.close();


        jsonStr = (String)jsonBuffer;
        jsonStr.trim();
        jsonStr = jsonStr.substring(0, jsonStr.lastIndexOf("}")+1);
//        jsonStr.remove(jsonStr.length());

        Serial.println(jsonStr);
        Serial.println("=====");

//        strcpy(jsonStr, jsonStr);

//        ddfreader.readDDF(String(jsonBuffer));

    }else Serial.println("fille too big! (6000 bytes max)");


    //ToDo: check functions...
}

void DDFreader::readDDF(String filename){


    String path = _ddfPath;
    String _filename = filename;
    path +=_filename;
    Serial.printf("Reading file: %s\n", path.c_str());

//    const char* pathStr = path.c_str();

    File file = SD.open(path.c_str());


    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("Read from file: ");
    uint16_t charCounter = 0;
    uint16_t fileSize = file.size();

    if(fileSize <= 6000){
    	char jsonBuffer[fileSize];

        while(file.available()){
        	jsonBuffer[charCounter] =  file.read();

//        	Serial.print(jsonBuffer[charCounter]);
        	charCounter++;
        }
        file.close();


        jsonStr = (String)jsonBuffer;
        jsonStr.trim();
        jsonStr = jsonStr.substring(0, jsonStr.lastIndexOf("}")+1);
//        jsonStr.remove(jsonStr.length());

        Serial.println(jsonStr);
        Serial.println("=====");

//        strcpy(jsonStr, jsonStr);

//        ddfreader.readDDF(String(jsonBuffer));

    }else Serial.println("fille too big! (6000 bytes max)");

//	strcpy(jsonStr, jsonString->c_str());	//put String to char array

	getDDFInformation();	//read DDF information
	getDDFfuncDimmer();
	getDDFfuncPosition();
	getDDFfuncPtspeed();
	getDDFfuncRgb();

}

void DDFreader::readDDF(String filename, DDFdevice *device){

    String path = _ddfPath;
    String _filename = filename;
    path +=_filename;
    Serial.printf("Reading file: %s\n", path.c_str());

//    const char* pathStr = path.c_str();

    File file = SD.open(path.c_str());


    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("Read from file: ");
    uint16_t charCounter = 0;
    uint16_t fileSize = file.size();

    if(fileSize <= 6000){
    	char jsonBuffer[fileSize];

        while(file.available()){
        	jsonBuffer[charCounter] =  file.read();

//        	Serial.print(jsonBuffer[charCounter]);
        	charCounter++;
        }
        file.close();


        jsonStr = (String)jsonBuffer;
        jsonStr.trim();
        jsonStr = jsonStr.substring(0, jsonStr.lastIndexOf("}")+1);
//        jsonStr.remove(jsonStr.length());

        Serial.println(jsonStr);
        Serial.println("=====");

//        strcpy(jsonStr, jsonStr);

//        ddfreader.readDDF(String(jsonBuffer));

    }else Serial.println("fille too big! (6000 bytes max)");

//	strcpy(jsonStr, jsonString->c_str());	//put String to char array

	getDDFInformation();	//read DDF information


	StaticJsonDocument<6000> doc;
	StaticJsonDocument<6000> filter;
	filter["device"]["functions"] = true;
	deserializeJson(doc, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
	serializeJsonPretty(doc, Serial);	//print object

	DDFdimmer _ddfDim;
	JsonObject obj = doc.to<JsonObject>();	//obosolet??
	JsonArray array = doc.to<JsonArray>();

	if(array.size() > 0){	//
		getDDFarrays();
	}else{	//single function group
		colorwheelArray[0] = getDDFfuncColorwheel();
		dimmerArray[0] = getDDFfuncDimmer();
		focusArray[0] = getDDFfuncFocus();
		frostArray[0] = getDDFfuncFrost();
		gobowheelArray[0] = getDDFfuncGobowheel();
		matrixArray[0] = getDDFfuncMatrix();
		positionArray[0] = getDDFfuncPosition();
		prismArray[0] = getDDFfuncPrism();
		ptspeedArray[0] = getDDFfuncPtspeed();
		rawArray[0] = getDDFfuncRaw();
		rgbArray[0] = getDDFfuncRgb();
		shutterArray[0] = getDDFfuncShutter();
		stepArray[0] = getDDFfuncStep();
		zoomArray[0] = getDDFfuncZoom();
	}


	getDDFarrays();
}

void DDFreader::getDDFInformation(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["information"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["information"] != NULL){	//if information NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.println("\n= information");

		//NESTED
		if(docNested["device"]["functions"]["information"]["electrical"]["static"]){	//if nested KEY exists
			const char* _electricalStatic = docNested["device"]["functions"]["information"]["electrical"]["static"];
			String _electricalStaticStr = String(_electricalStatic);
			if(_electricalStaticStr == "" || _electricalStaticStr == "0"){
				deviceInfo.info.electricalStatic = 0;
			}else{
				if(_electricalStaticStr.toInt() > 0){
					deviceInfo.info.electricalStatic = _electricalStaticStr.toInt();
				}
			}
			Serial.print("=== electr. static:\t");Serial.println(deviceInfo.info.electricalStatic);
		}else{
			Serial.println("=== -no electr. static");
		}
		if(docNested["device"]["information"]["electrical"]["dimmer"]){	//if nested KEY exists
			const char* _electricalDimmer = docNested["device"]["functions"]["information"]["electrical"]["dimmer"];
			String _electricalDimmerStr = String(_electricalDimmer);
			if(_electricalDimmerStr == "" || _electricalDimmerStr == "0"){
				deviceInfo.info.electricalDimmer = 0;
			}else{
				if(_electricalDimmerStr.toInt() > 0){
					deviceInfo.info.electricalDimmer = _electricalDimmerStr.toInt();
				}
			}
			Serial.print("=== electr. static:\t");Serial.println(deviceInfo.info.electricalDimmer);
		}else{
			Serial.println("=== -no electr. static");
		}

		//DIRECT
		StaticJsonDocument<1000> docDirect;
		deserializeJson(docDirect, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

		if(docDirect["device"]["information"]["ddf-library-id"]){	//if KEY exists
			const char* libId = docDirect["device"]["information"]["ddf-library-id"];
			deviceInfo.info.ddfLibraryId = String(libId);
			Serial.print("== ddf-library-id:\t");Serial.println(deviceInfo.info.ddfLibraryId);
		}else{
			Serial.println("== -no ddf-library-id (ERRR)");
		}

		if(docDirect["device"]["information"]["model"]){	//if KEY exists
			const char* _model = docDirect["device"]["information"]["model"];
			deviceInfo.info.model = String(_model);
			Serial.print("== model:\t");Serial.println(deviceInfo.info.model);
		}else{
			Serial.println("== -no model(ERRR)");
		}

		if(docDirect["device"]["information"]["vendor"]){	//if KEY exists
			const char* _vendor = docDirect["device"]["information"]["vendor"];
			deviceInfo.info.vendor = String(_vendor);
			Serial.print("== model:\t");Serial.println(deviceInfo.info.vendor);
		}else{
			Serial.println("== -no vendor(ERRR)");
		}

		if(docDirect["device"]["information"]["author"]){	//if KEY exists
			const char* _author = docDirect["device"]["information"]["author"];
			deviceInfo.info.author = String(_author);
			Serial.print("== author:\t");Serial.println(deviceInfo.info.author);
		}else{
			Serial.println("== -no author(ERRR)");
		}

		if(docDirect["device"]["information"]["mode"]){	//if KEY exists
			const char* _mode = docDirect["device"]["information"]["mode"];
			deviceInfo.info.mode = String(_mode);
			Serial.print("== mode:\t");Serial.println(deviceInfo.info.mode);
		}else{
			Serial.println("== -no mode(ERRR)");
		}
	}
}

void DDFreader::getDDFarrays(){
	uint16_t arrayCounter = 0;
	DDFdimmer _dimSub;
	DDFdimmer *_dimArr;

	getDDFarrays();
	do{
		_dimSub = getDDFfuncDimmerArray(arrayCounter);
	if(_dimSub.exist){
		arrayCounter++;
		_dimArr = new DDFdimmer[deviceInfo.dimmerCount];	//array with new size
		for(int i = 0; i < deviceInfo.dimmerCount -1; i++){
			_dimArr[i] = dimmerArray[i];	//fill new array without last entry
		}
		_dimArr[deviceInfo.dimmerCount-1] = _dimSub;

		delete []dimmerArray;	//delete old array
		dimmerArray = _dimArr;	//fill array with new array (with new size)
		_dimArr = NULL;	//delete location of pointer _dimArry
	}
	}while(_dimSub.exist);
}


DDFdimmer DDFreader::getDDFfuncDimmer(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["dimmer"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
	serializeJsonPretty(docNested, Serial);	//print object

	DDFdimmer _ddfDim;
	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["functions"]["dimmer"] != NULL){	//if dimmer NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.printf("\n= dimmer");

		//NESTED
		bool hasRange = false;
		if(docNested["device"]["functions"]["dimmer"]["range"]["_type"]){	//if ["range"] KEY exists
			const char* _type = docNested["device"]["functions"]["dimmer"]["range"]["_type"];
			String _typeStr = String(_type);

			if(_typeStr == "linear"){
				_ddfDim.type = curve_linear;
			}else{
				_ddfDim.type = -1;	//unknown
			}
			Serial.print("== _type:\t");Serial.println(_type);
			hasRange = true;
			deviceInfo.dimmerCount++;
		}else{
//			Serial.println("== -no _type");
		}
		if(docNested["device"]["functions"]["dimmer"]["range"]["_mindmx"]){	//if ["range"] KEY exists
			_ddfDim.mindmx = docNested["device"]["functions"]["dimmer"]["range"]["_mindmx"];
			Serial.print("== _mindmx:\t");Serial.println(_ddfDim.mindmx);
			hasRange = true;
		}else{
//			Serial.println("== -no _mindmx");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_maxdmx"]){	//if ["range"] KEY exists
			_ddfDim.maxdmx = docNested["device"]["functions"]["dimmer"]["range"]["_maxdmx"];
			Serial.print("== _maxdmx:\t");Serial.println(_ddfDim.maxdmx);
			hasRange = true;
		}else{
//			Serial.println("== -no _maxdmx");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_minval"]){	//if ["range"] KEY exists
			_ddfDim.minval = docNested["device"]["functions"]["dimmer"]["range"]["_minval"];
			Serial.print("== _minval:\t");Serial.println(_ddfDim.minval);
			hasRange = true;
		}else{
//			Serial.println("== -no _minval");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_maxval"]){	//if ["range"] KEY exists
			_ddfDim.maxval = docNested["device"]["functions"]["dimmer"]["range"]["_maxval"];
			Serial.print("== _maxval:\t");Serial.println(_ddfDim.maxval);
			hasRange = true;
		}else{
//			Serial.println("== -no _maxval");
		}
//		if(hasRange)Serial.println("== hasRange");
//		else Serial.println("== -no Range");

		//DIRECT
		StaticJsonDocument<1000> docDirect;
		deserializeJson(docDirect, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

		if(docDirect["device"]["functions"]["dimmer"]["_dmxchannel"]){	//if _dmxchannel KEY exists
			_ddfDim.dmxchannel = docDirect["device"]["functions"]["dimmer"]["_dmxchannel"];
			Serial.print("== dmxchannel:\t");Serial.println(_ddfDim.dmxchannel);
			if(docDirect["device"]["functions"]["dimmer"]["_finedmxchannel"]){	//if _finedmxchannel KEY exists
				_ddfDim.finedmxchannel = docDirect["device"]["functions"]["dimmer"]["_finedmxchannel"];
				Serial.print("== finedmxchannel:\t");Serial.println(_ddfDim.finedmxchannel);
			}else{
//				Serial.println("== -no _finedmxchannel");
			}
		}else{
			Serial.println("== -no _dmxchannel (ERRR)");
		}
	}

	if(_ddfDim.dmxchannel >=0){
		_ddfDim.exist = true;
	}

	//array of dimmer

	return _ddfDim;
}

DDFdimmer DDFreader::getDDFfuncDimmerArray(uint16_t no){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"][no]["dimmer"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
	serializeJsonPretty(docNested, Serial);	//print object

	DDFdimmer _ddfDim;
	_ddfDim.isMaster = false;
	deviceInformation_t _subInfo;
	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["functions"][no]["dimmer"] != NULL){	//if dimmer NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.printf("\n= dimmer");

		//NESTED
		bool hasRange = false;
		if(docNested["device"]["functions"]["dimmer"][no]["range"]["_type"]){	//if ["range"] KEY exists
			const char* _type = docNested["device"]["functions"][no]["dimmer"]["range"]["_type"];
			String _typeStr = String(_type);

			if(_typeStr == "linear"){
				_ddfDim.type = curve_linear;
			}else{
				_ddfDim.type = -1;	//unknown
			}
			Serial.print("== _type:\t");Serial.println(_type);
			hasRange = true;
		}else{
//			Serial.println("== -no _type");
		}
		if(docNested["device"]["functions"][no]["dimmer"]["range"]["_mindmx"]){	//if ["range"] KEY exists
			_ddfDim.mindmx = docNested["device"]["functions"][no]["dimmer"]["range"]["_mindmx"];
			Serial.print("== _mindmx:\t");Serial.println(_ddfDim.mindmx);
			hasRange = true;
		}else{
//			Serial.println("== -no _mindmx");
		}

		if(docNested["device"]["functions"][no]["dimmer"]["range"]["_maxdmx"]){	//if ["range"] KEY exists
			_ddfDim.maxdmx = docNested["device"]["functions"][no]["dimmer"]["range"]["_maxdmx"];
			Serial.print("== _maxdmx:\t");Serial.println(_ddfDim.maxdmx);
			hasRange = true;
		}else{
//			Serial.println("== -no _maxdmx");
		}

		if(docNested["device"]["functions"][no]["dimmer"]["range"]["_minval"]){	//if ["range"] KEY exists
			_ddfDim.minval = docNested["device"]["functions"][no]["dimmer"]["range"]["_minval"];
			Serial.print("== _minval:\t");Serial.println(_ddfDim.minval);
			hasRange = true;
		}else{
//			Serial.println("== -no _minval");
		}

		if(docNested["device"]["functions"][no]["dimmer"]["range"]["_maxval"]){	//if ["range"] KEY exists
			_ddfDim.maxval = docNested["device"]["functions"][no]["dimmer"]["range"]["_maxval"];
			Serial.print("== _maxval:\t");Serial.println(_ddfDim.maxval);
			hasRange = true;
		}else{
//			Serial.println("== -no _maxval");
		}
//		if(hasRange)Serial.println("== hasRange");
//		else Serial.println("== -no Range");

		//DIRECT
		StaticJsonDocument<1000> docDirect;
		deserializeJson(docDirect, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

		if(docDirect["device"]["functions"][no]["dimmer"]["_dmxchannel"]){	//if _dmxchannel KEY exists
			_ddfDim.dmxchannel = docDirect["device"]["functions"][no]["dimmer"]["_dmxchannel"];


			Serial.print("== dmxchannel:\t");Serial.println(_ddfDim.dmxchannel);

			if(docDirect["device"]["functions"][no]["dimmer"]["_finedmxchannel"]){	//if _finedmxchannel KEY exists
				_ddfDim.finedmxchannel = docDirect["device"]["functions"][no]["dimmer"]["_finedmxchannel"];
				Serial.print("== finedmxchannel:\t");Serial.println(_ddfDim.finedmxchannel);
			}else{
//				Serial.println("== -no _finedmxchannel");
			}
		}else{
			Serial.println("== -no _dmxchannel (ERRR)");
		}
	}

	if(_ddfDim.dmxchannel >=0){
		_ddfDim.exist = true;
		deviceInfo.dimmerCount++;
	}

	//array of dimmer

	return _ddfDim;
}

DDFposition DDFreader::getDDFfuncPosition(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["position"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

//	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();
	bool hasPan = false;
	bool hastilt = false;
	DDFposition _ddfPos;

	if(obj["device"]["functions"]["position"] != NULL){	//if dimmer NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
//		Serial.println("\n= position");

		//NESTED
		//pan

		if(docNested["device"]["functions"]["position"]["pan"]["range"]["_range"]){	//if nested KEY exists
			_ddfPos.pan_range = docNested["device"]["functions"]["position"]["pan"]["range"]["_range"];
			Serial.print("=== _rangePan:\t");Serial.println(_ddfPos.pan_range);
			hasPan = true;
		}else{
//			Serial.println("=== -no _rangePan");
		}

		if(docNested["device"]["functions"]["position"]["pan"]["_dmxchannel"]){	//if nested KEY exists
			_ddfPos.pan_dmxchannel = docNested["device"]["functions"]["position"]["pan"]["_dmxchannel"];
			Serial.print("== panDmxchannel:\t");Serial.println(_ddfPos.pan_dmxchannel);
			hasPan = true;
			if(docNested["device"]["functions"]["position"]["pan"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfPos.pan_finedmxchannel = docNested["device"]["functions"]["position"]["pan"]["_finedmxchannel"];
				Serial.print("== panFinedmxchannel:\t");Serial.println(_ddfPos.pan_finedmxchannel);
			}else{
//				Serial.println("== -no panFinedmxchannel");
			}
		}else{
//			Serial.println("== -no panDmxchannel");
		}

		//tilt

		if(docNested["device"]["functions"]["position"]["tilt"]["range"]["_range"]){	//if nested KEY exists
			_ddfPos.tilt_range = docNested["device"]["functions"]["position"]["tilt"]["range"]["_range"];
			Serial.print("=== _rangetilt:\t");Serial.println(_ddfPos.tilt_range);
			hastilt = true;
		}else{
//			Serial.println("=== -no _rangetilt");
		}

		if(docNested["device"]["functions"]["position"]["tilt"]["_dmxchannel"]){	//if nested KEY exists
			_ddfPos.tilt_dmxchannel = docNested["device"]["functions"]["position"]["tilt"]["_dmxchannel"];
			Serial.print("== tiltDmxchannel:\t");Serial.println(_ddfPos.tilt_dmxchannel);
			hastilt = true;
			if(docNested["device"]["functions"]["position"]["tilt"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfPos.tilt_finedmxchannel = docNested["device"]["functions"]["position"]["tilt"]["_finedmxchannel"];
				Serial.print("== tiltFinedmxchannel:\t");Serial.println(_ddfPos.tilt_finedmxchannel);
			}else{
//				Serial.println("== -no tiltFinedmxchannel");
			}
		}else{
//			Serial.println("== -no tiltDmxchannel");
		}
	}

	if(hasPan || hastilt){
		_ddfPos.exist = true;
	}

	return _ddfPos;
}

void DDFreader::getDDFfuncPtspeed(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["ptspeed"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

//	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["functions"]["ptspeed"] != NULL){	//if dimmer NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.println("\n= ptspeed");
		//NESTED
		bool hasRange = false;
		if(docNested["device"]["functions"]["ptspeed"]["range"]["_type"]){	//if ["range"] KEY exists
			const char* _type = docNested["device"]["functions"]["ptspeed"]["range"]["_type"];
			Serial.print("== _type:\t");Serial.println(_type);
			hasRange = true;
		}else{
			Serial.println("== -no _type");
		}
		if(docNested["device"]["functions"]["ptspeed"]["range"]["_mindmx"]){	//if ["range"] KEY exists
			int _mindmx = docNested["device"]["functions"]["ptspeed"]["range"]["_mindmx"];
			Serial.print("== _mindmx:\t");Serial.println(_mindmx);
			hasRange = true;
		}else{
			Serial.println("== -no _mindmx");
		}

		if(docNested["device"]["functions"]["ptspeed"]["range"]["_maxdmx"]){	//if ["range"] KEY exists
			int _maxdmx = docNested["device"]["functions"]["ptspeed"]["range"]["_maxdmx"];
			Serial.print("== _maxdmx:\t");Serial.println(_maxdmx);
			hasRange = true;
		}else{
			Serial.println("== -no _maxdmx");
		}

		if(docNested["device"]["functions"]["ptspeed"]["range"]["_minval"]){	//if ["range"] KEY exists
			double _minval = docNested["device"]["functions"]["ptspeed"]["range"]["_minval"];
			Serial.print("== _minval:\t");Serial.println(_minval);
			hasRange = true;
		}else{
			Serial.println("== -no _minval");
		}

		if(docNested["device"]["functions"]["ptspeed"]["range"]["_maxval"]){	//if ["range"] KEY exists
			double _maxval = docNested["device"]["functions"]["ptspeed"]["range"]["_maxval"];
			Serial.print("== _maxval:\t");Serial.println(_maxval);
			hasRange = true;
		}else{
			Serial.println("== -no _maxval");
		}
		if(hasRange)Serial.println("== hasRange");
		else Serial.println("== -no Range");

		//DIRECT
		StaticJsonDocument<1000> docDirect;
		deserializeJson(docDirect, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

		if(docDirect["device"]["functions"]["ptspeed"]["_dmxchannel"]){	//if _dmxchannel KEY exists
			int dmxchannel = docDirect["device"]["functions"]["ptspeed"]["_dmxchannel"];
			Serial.print("== dmxchannel:\t");Serial.println(dmxchannel);
			if(docDirect["device"]["functions"]["ptspeed"]["_finedmxchannel"]){	//if _finedmxchannel KEY exists
				int _finedmxchannel = docDirect["device"]["functions"]["ptspeed"]["_finedmxchannel"];
				Serial.print("== finedmxchannel:\t");Serial.println(_finedmxchannel);
			}else{
				Serial.println("== -no _finedmxchannel");
			}
		}else{
			Serial.println("== -no _dmxchannel (ERRR)");
		}
	}
}

DDFrgb DDFreader::getDDFfuncRgb(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["rgb"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

//	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();
	DDFrgb _ddfRgb;

	if(obj["device"]["functions"]["rgb"] != NULL){	//if NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
//		Serial.println("\n= rgb");
		//NESTED
		bool hasRed = false;
		if(docNested["device"]["functions"]["rgb"]["red"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.redDmxchannel = docNested["device"]["functions"]["rgb"]["red"]["_dmxchannel"];
			Serial.print("== redDmxchannel:\t");Serial.println(_ddfRgb.redDmxchannel);
			hasRed = true;
			if(docNested["device"]["functions"]["rgb"]["red"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.redFinedmxchannel = docNested["device"]["functions"]["rgb"]["red"]["_finedmxchannel"];
				Serial.print("== redFineDmxchannel:\t");Serial.println(_ddfRgb.redFinedmxchannel);
			}else{
//				Serial.println("== -no redFineDmxchannel");
			}
		}else{
//			Serial.println("== -no redDmxchannel");
		}

		bool hasGreen = false;
		if(docNested["device"]["functions"]["rgb"]["green"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.greenDmxchannel = docNested["device"]["functions"]["rgb"]["green"]["_dmxchannel"];
			Serial.print("== greenDmxchannel:\t");Serial.println(_ddfRgb.greenDmxchannel);
			hasGreen = true;
			if(docNested["device"]["functions"]["rgb"]["green"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.greenFinedmxchannel = docNested["device"]["functions"]["rgb"]["green"]["_finedmxchannel"];
				Serial.print("== greenFineDmxchannel:\t");Serial.println(_ddfRgb.greenFinedmxchannel);
			}else{
//				Serial.println("== -no greenFineDmxchannel");
			}
		}else{
//			Serial.println("== -no greenDmxchannel");
		}

		bool hasBlue = false;
		if(docNested["device"]["functions"]["rgb"]["blue"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.blueDmxchannel = docNested["device"]["functions"]["rgb"]["blue"]["_dmxchannel"];
			Serial.print("== blueDmxchannel:\t");Serial.println(_ddfRgb.blueDmxchannel);
			hasBlue = true;
			if(docNested["device"]["functions"]["rgb"]["blue"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.blueFinedmxchannel = docNested["device"]["functions"]["rgb"]["blue"]["_finedmxchannel"];
				Serial.print("== blueFineDmxchannel:\t");Serial.println(_ddfRgb.blueFinedmxchannel);
			}else{
//				Serial.println("== -no blueFineDmxchannel");
			}
		}else{
//			Serial.println("== -no blueDmxchannel");
		}

		bool hasWhite = false;
		if(docNested["device"]["functions"]["rgb"]["white"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.whiteDmxchannel = docNested["device"]["functions"]["rgb"]["white"]["_dmxchannel"];
			Serial.print("== whiteDmxchannel:\t");Serial.println(_ddfRgb.whiteDmxchannel);
			hasWhite = true;
			if(docNested["device"]["functions"]["rgb"]["white"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.whiteFinedmxchannel = docNested["device"]["functions"]["rgb"]["white"]["_finedmxchannel"];
				Serial.print("== whiteFineDmxchannel:\t");Serial.println(_ddfRgb.whiteFinedmxchannel);
			}else{
//				Serial.println("== -no whiteFineDmxchannel");
			}
		}else{
//			Serial.println("== -no whiteDmxchannel");
		}


		bool hasAmber = false;
		if(docNested["device"]["functions"]["rgb"]["amber"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.amberDmxchannel = docNested["device"]["functions"]["rgb"]["amber"]["_dmxchannel"];
			Serial.print("== amberDmxchannel:\t");Serial.println(_ddfRgb.amberDmxchannel);
			hasAmber = true;
			if(docNested["device"]["functions"]["rgb"]["amber"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.amberFinedmxchannel = docNested["device"]["functions"]["rgb"]["amber"]["_finedmxchannel"];
				Serial.print("== amberFineDmxchannel:\t");Serial.println(_ddfRgb.amberFinedmxchannel);
			}else{
//				Serial.println("== -no amberFineDmxchannel");
			}
		}else{
//			Serial.println("== -no amberDmxchannel");
		}

		bool hasUv = false;
		if(docNested["device"]["functions"]["rgb"]["uv"]["_dmxchannel"]){	//if nested KEY exists
			_ddfRgb.uvDmxchannel = docNested["device"]["functions"]["rgb"]["uv"]["_dmxchannel"];
			Serial.print("== uvDmxchannel:\t");Serial.println(_ddfRgb.uvDmxchannel);
			hasUv = true;
			if(docNested["device"]["functions"]["rgb"]["uv"]["_finedmxchannel"]){	//if nested KEY exists
				_ddfRgb.uvFinedmxchannel = docNested["device"]["functions"]["rgb"]["uv"]["_finedmxchannel"];
				Serial.print("== uvFineDmxchannel:\t");Serial.println(_ddfRgb.uvFinedmxchannel);
			}else{
				Serial.println("== -no uvFineDmxchannel");
			}
		}else{
			Serial.println("== -no uvDmxchannel");
		}

	}
	return _ddfRgb;
}

void DDFreader::getDDFfuncRawstep(){	//ToDo: implementieren
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["rawstep"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

//	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["functions"]["rgb"] != NULL){	//if NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.println("\n= rgb");
		//NESTED
		bool hasRed = false;
		if(docNested["device"]["functions"]["rgb"]["red"]["_dmxchannel"]){	//if nested KEY exists
			const char* redDmxchannel = docNested["device"]["functions"]["rgb"]["red"]["_dmxchannel"];
			Serial.print("== redDmxchannel:\t");Serial.println(redDmxchannel);
			hasRed = true;
			if(docNested["device"]["functions"]["rgb"]["red"]["_finedmxchannel"]){	//if nested KEY exists
				const char* redFineDmxchannel = docNested["device"]["functions"]["rgb"]["red"]["_finedmxchannel"];
				Serial.print("== redFineDmxchannel:\t");Serial.println(redFineDmxchannel);
			}else{
				Serial.println("== -no redFineDmxchannel");
			}
		}else{
			Serial.println("== -no redDmxchannel");
		}

		bool hasGreen = false;
		if(docNested["device"]["functions"]["rgb"]["green"]["_dmxchannel"]){	//if nested KEY exists
			const char* greenDmxchannel = docNested["device"]["functions"]["rgb"]["green"]["_dmxchannel"];
			Serial.print("== greenDmxchannel:\t");Serial.println(greenDmxchannel);
			hasGreen = true;
			if(docNested["device"]["functions"]["rgb"]["green"]["_finedmxchannel"]){	//if nested KEY exists
				const char* greenFineDmxchannel = docNested["device"]["functions"]["rgb"]["green"]["_finedmxchannel"];
				Serial.print("== greenFineDmxchannel:\t");Serial.println(greenFineDmxchannel);
			}else{
				Serial.println("== -no greenFineDmxchannel");
			}
		}else{
			Serial.println("== -no greenDmxchannel");
		}

		bool hasBlue = false;
		if(docNested["device"]["functions"]["rgb"]["blue"]["_dmxchannel"]){	//if nested KEY exists
			const char* blueDmxchannel = docNested["device"]["functions"]["rgb"]["blue"]["_dmxchannel"];
			Serial.print("== blueDmxchannel:\t");Serial.println(blueDmxchannel);
			hasBlue = true;
			if(docNested["device"]["functions"]["rgb"]["blue"]["_finedmxchannel"]){	//if nested KEY exists
				const char* blueFineDmxchannel = docNested["device"]["functions"]["rgb"]["blue"]["_finedmxchannel"];
				Serial.print("== blueFineDmxchannel:\t");Serial.println(blueFineDmxchannel);
			}else{
				Serial.println("== -no blueFineDmxchannel");
			}
		}else{
			Serial.println("== -no blueDmxchannel");
		}

		bool hasWhite = false;
		if(docNested["device"]["functions"]["rgb"]["white"]["_dmxchannel"]){	//if nested KEY exists
			const char* whiteDmxchannel = docNested["device"]["functions"]["rgb"]["white"]["_dmxchannel"];
			Serial.print("== whiteDmxchannel:\t");Serial.println(whiteDmxchannel);
			hasWhite = true;
			if(docNested["device"]["functions"]["rgb"]["white"]["_finedmxchannel"]){	//if nested KEY exists
				const char* whiteFineDmxchannel = docNested["device"]["functions"]["rgb"]["white"]["_finedmxchannel"];
				Serial.print("== whiteFineDmxchannel:\t");Serial.println(whiteFineDmxchannel);
			}else{
				Serial.println("== -no whiteFineDmxchannel");
			}
		}else{
			Serial.println("== -no whiteDmxchannel");
		}


		bool hasAmber = false;
		if(docNested["device"]["functions"]["rgb"]["amber"]["_dmxchannel"]){	//if nested KEY exists
			const char* amberDmxchannel = docNested["device"]["functions"]["rgb"]["amber"]["_dmxchannel"];
			Serial.print("== amberDmxchannel:\t");Serial.println(amberDmxchannel);
			hasAmber = true;
			if(docNested["device"]["functions"]["rgb"]["amber"]["_finedmxchannel"]){	//if nested KEY exists
				const char* amberFineDmxchannel = docNested["device"]["functions"]["rgb"]["amber"]["_finedmxchannel"];
				Serial.print("== amberFineDmxchannel:\t");Serial.println(amberFineDmxchannel);
			}else{
				Serial.println("== -no amberFineDmxchannel");
			}
		}else{
			Serial.println("== -no amberDmxchannel");
		}

		bool hasUv = false;
		if(docNested["device"]["functions"]["rgb"]["uv"]["_dmxchannel"]){	//if nested KEY exists
			const char* uvDmxchannel = docNested["device"]["functions"]["rgb"]["uv"]["_dmxchannel"];
			Serial.print("== uvDmxchannel:\t");Serial.println(uvDmxchannel);
			hasUv = true;
			if(docNested["device"]["functions"]["rgb"]["uv"]["_finedmxchannel"]){	//if nested KEY exists
				const char* uvFineDmxchannel = docNested["device"]["functions"]["rgb"]["uv"]["_finedmxchannel"];
				Serial.print("== uvFineDmxchannel:\t");Serial.println(uvFineDmxchannel);
			}else{
				Serial.println("== -no uvFineDmxchannel");
			}
		}else{
			Serial.println("== -no uvDmxchannel");
		}

	}
}

void DDFreader::getDDFfuncFocus(){
	StaticJsonDocument<1000> docNested;
	StaticJsonDocument<1000> filter;
	filter["device"]["functions"]["focus"] = true;
	deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

//	serializeJsonPretty(docNested, Serial);	//print object

	JsonObject obj = docNested.to<JsonObject>();

	if(obj["device"]["functions"]["focus"] != NULL){	//if dimmer NESTED key exists (obj != NULL)
		deserializeJson(docNested, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter
		Serial.println("\n= focus");

		//NESTED
		bool hasRange = false;
		if(docNested["device"]["functions"]["dimmer"]["range"]["_type"]){	//if ["range"] KEY exists
			const char* _type = docNested["device"]["functions"]["dimmer"]["range"]["_type"];
			Serial.print("== _type:\t");Serial.println(_type);
			hasRange = true;
		}else{
			Serial.println("== -no _type");
		}
		if(docNested["device"]["functions"]["dimmer"]["range"]["_mindmx"]){	//if ["range"] KEY exists
			int _mindmx = docNested["device"]["functions"]["dimmer"]["range"]["_mindmx"];
			Serial.print("== _mindmx:\t");Serial.println(_mindmx);
			hasRange = true;
		}else{
			Serial.println("== -no _mindmx");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_maxdmx"]){	//if ["range"] KEY exists
			int _maxdmx = docNested["device"]["functions"]["dimmer"]["range"]["_maxdmx"];
			Serial.print("== _maxdmx:\t");Serial.println(_maxdmx);
			hasRange = true;
		}else{
			Serial.println("== -no _maxdmx");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_minval"]){	//if ["range"] KEY exists
			double _minval = docNested["device"]["functions"]["dimmer"]["range"]["_minval"];
			Serial.print("== _minval:\t");Serial.println(_minval);
			hasRange = true;
		}else{
			Serial.println("== -no _minval");
		}

		if(docNested["device"]["functions"]["dimmer"]["range"]["_maxval"]){	//if ["range"] KEY exists
			double _maxval = docNested["device"]["functions"]["dimmer"]["range"]["_maxval"];
			Serial.print("== _maxval:\t");Serial.println(_maxval);
			hasRange = true;
		}else{
			Serial.println("== -no _maxval");
		}
		if(hasRange)Serial.println("== hasRange");
		else Serial.println("== -no Range");

		//DIRECT
		StaticJsonDocument<300> docDirect;
		deserializeJson(docDirect, jsonStr, DeserializationOption::Filter(filter));// Deserialize the document with filter

		if(docDirect["device"]["functions"]["dimmer"]["_dmxchannel"]){	//if _dmxchannel KEY exists
			int dmxchannel = docDirect["device"]["functions"]["dimmer"]["_dmxchannel"];
			Serial.print("== dmxchannel:\t");Serial.println(dmxchannel);
		}else{
			Serial.println("== -no _dmxchannel (ERRR)");
		}

		if(docDirect["device"]["functions"]["dimmer"]["_finedmxchannel"]){	//if _finedmxchannel KEY exists
			int _finedmxchannel = docDirect["device"]["functions"]["dimmer"]["_finedmxchannel"];
			Serial.print("== finedmxchannel:\t");Serial.println(_finedmxchannel);
		}else{
			Serial.println("== -no _finedmxchannel");
		}


	}
}
