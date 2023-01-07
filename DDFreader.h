/*
 * DDFreader.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef DDFREADER_H_
#define DDFREADER_H_
#include "Arduino.h"
#include "DDF_defines.h"	//defines & structs for DDFreader
#include "DDFdevice.h"	//DDFdevice class
#include "DDFcheck.h"
#include "AbstractDDFfunction.h"
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <TinyXML.h>

#include "DDFdimmers.h"	//dimmers, rgbs, steps... objects
#include "DDFrgbs.h"
#include "DDFpositions.h"
#include "DDFsteps.h"
#include "DDFfocusses.h"
#include "DDFfrosts.h"
#include "DDFgobowheels.h"
#include "DDFcolorwheels.h"
#include "DDFmatrices.h"
#include "DDFprisms.h"
#include "DDFptspeeds.h"
#include "DDFraws.h"
#include "DDFshutters.h"	//ToDo: implement im Detail (shutter funktionen etc.)
#include "DDFzooms.h"


class DDFreader{
	friend class DDFdevice;
public:
	
	DDFreader(TinyXML *xml);	//constructor with pointer to tinyXML object
	static void init();	//initialize SD card etc.
	static void setDDFpath(String path);	//set folderpath
	static void XMLcallback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen );	//callback function for xml processing
	static void readDDF(String filename);	//read DDF (with no return)


private:

	static String currentTag;	//current Tag
	static String currentRainbowtype;	//current rainbow type (colorwheel)
	static void startTag(String tagName);
	static void tag(String tagName, String data);	//process tag
	static void attribute(String tagName, String data);	//process attribute
	static void processDmxchannel(String data);	//process attribute "dmxchannel"
	static void processFinedmx(String data);	//process attribute "finedmxchannel"
	static void processRange(String data);	//process attribute "range"
	static void processType(String data);	//process attribute "type"
	static void processVal(String data);
	static void processCaption(String data);
	static void processMindmx(String data);
	static void processMaxdmx(String data);

	static void endTag(String tagName);
	

	static void tagDevice(String text);
	static void tagDeviceInformation(String text);


	// int _length;	//ToDo: obsolet?
	static TinyXML *xml;

	static String _ddfPath;

	static String currentTag;	//indicates, what type of function is begin read in from xml
	static ddfInformation_t ddfInfo;	//ddf information (vendor, author, model etc.)
	static deviceInformation_t deviceInfo;	//device information (amount of dimmers, rgb etc.)

	static colorwheel_t* colorwheelArray;	//temp arrays
	static singlecolor_t* colorArray;
	static DDFdimmer* dimmerArray;
	static DDFfocus* focusArray;
	static DDFfrost* frostArray;
	static gobowheel_t* gobowheelArray;
	static singlegobo_t* goboArray;
	static DDFmatrix* matrixArray;
	static DDFposition* positionArray;
	static DDFprism* prismArray;
	static DDFptspeed* ptspeedArray;
	static DDFraw* rawArray;
	static DDFrgb* rgbArray;
	static DDFshutter* shutterArray;
	static DDFstep* stepfuncArray;
	static singlestep_t* stepArray;
	static DDFzoom* zoomArray;

}; extern DDFreader DDF;

#endif /* LIBRARIES_DDFREADER_DDFREADER_H_ */
