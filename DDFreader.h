/*
 * DDFreader.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef DDFREADER_H_
#define DDFREADER_H_

#include "Arduino.h"
#include "DDFdevice.h"
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

#define DDFBUFSIZE 6000	//Bytes

#define PIN_SPI_MOSI 23
#define PIN_SPI_MISO 19
#define PIN_SPI_SCK 18
#define PIN_SPI_CSSD 5

/* XML TAGS */
#define TAG_DEVICE "/device"
#define TEXT_DEVICETYPE "/device/type"
#define TEXT_DMXCVERSION "/device/dmxcversion"
#define TEXT_DDFVERSION "/device/ddfversion"

#define TAG_INFO_LIBID_START "/device/information/ddf-library-id"
#define TAG_INFO_MODEL "/device/information/model"
#define TAG_INFO_VENDOR "/device/information/vendor"
#define TAG_INFO_AUTHOR "/device/information/author"
#define TAG_INFO_MODE "/device/information/mode"
#define TAG_INO_ELECTRICAL "/device/information/electrical"
#define TAG_INO_ELECTRICAL_STATIC "/device/information/electrical/static"
#define TAG_INO_ELECTRICAL_dimmer "/device/information/electrical/dimmer"

#define TAG_FUNCTIONS_COLORWHEEL "/device/functions/colorwheel"
#define TAG_FUNCTIONS_DIMMER "/device/functions/dimmer"
#define TAG_FUNCTIONS_FOCUS "/device/functions/focus"
#define TAG_FUNCTIONS_FROST  "/device/functions/frost"
#define TAG_FUNCTIONS_GOBOWHEEL  "/device/functions/gobowheel"
#define TAG_FUNCTIONS_MATRIX "/device/functions/matrix"
#define TAG_FUNCTIONS_POSITION "/device/functions/position"
#define TAG_FUNCTIONS_POSITION_PAN "/device/functions/position/pan"
#define TEXT_FUNCTIONS_POSITION_PAN_DMMXCHANNEL "/device/functions/position/pan/dmxchannel"	//ToDo: tags/text richtig??
#define TEXT_FUNCTIONS_POSITION_PAN_DMMXCHANNEL "/device/functions/position/pan/finedmxchannel"
#define TEXT_FUNCTIONS_POSITION_PAN_RANGE "/device/functions/position/pan/range/range"
#define TAG_FUNCTIONS_POSITION_PTILT "/device/functions/position/tilt"
#define TAG_FUNCTIONS_PRISM "/device/functions/prism"
#define TAG_FUNCTIONS_PTSPEED "/device/functions/ptspeed"
#define TAG_FUNCTIONS_RAW "/device/functions/raw"
#define TAG_FUNCTIONS_RGB "/device/functions/rgb"
#define TAG_FUNCTIONS_SHUTTER "/device/functions/shutter"
#define TAG_FUNCTIONS_STEP "/device/functions/step"
#define TAG_FUNCTIONS_ZOOM "/device/functions/zoom"

struct ddfInformation_t{
	String ddfLibraryId = "";
	String model = "";
	String vendor = "";
	String author = "";
	String mode = "";
	String image = "";
	int dmxaddresscount = -1;
	int dmxcversion[3] = {-1,-1,-1};
	int ddfversion[3] = {-1,-1,-1};
	int electricalStatic = 0;
	int electricalDimmer = 0;
};

struct deviceInformation_t{
	bool readSucess = true;

	ddfInformation_t info;

	uint16_t functioncount = 0;

	int colorwheelCount = -1;
	int dimmerCount = -1;
	int focusCount = -1;
	int frostCount = -1;
	int gobowheelCount = -1;
	int matrixCount = -1;
	int positionCount = -1;
	int prismCount = -1;
	int ptspeedCount = -1;
	int rawCount = -1;
	int rgbCount = -1;
	int shutterCount = -1;
	int StepCount = -1;
	int ZoomCount = -1;

};


class DDFreader{
	friend class DDFdevice;
public:
	
	DDFreader(TinyXML *xml);	//constructor with pointer to tinyXML object
	static void init();	//initialize SD card etc.
	static void setDDFpath(String path);	//set folderpath
	static void XMLcallback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen );	//callback function for xml processing
	static void readDDF(String filename);	//read DDF (with no return)


private:

	static String currentTag;
	static void startTag(String tagName);
	static void tagDevice(String text);
	static void tagDeviceInformation(String text);


	// int _length;	//ToDo: obsolet?
	static TinyXML *xml;

	static String _ddfPath;

	static ddfInformation_t ddfInfo;
	static deviceInformation_t deviceInfo;

	colorwheel_t* colorwheelArray;	//temp array
	singlecolor_t* colorArray;
	DDFdimmer* dimmerArray;
	DDFfocus* focusArray;
	DDFfrost* frostArray;
	gobowheel_t* gobowheelArray;
	singlegobo_t* goboArray;
	DDFmatrix* matrixArray;
	DDFposition* positionArray;
	DDFprism* prismArray;
	DDFptspeed* ptspeedArray;
	DDFraw* rawArray;
	DDFrgb* rgbArray;
	DDFshutter* shutterArray;
	stepfunc_t* stepfuncArray;
	singlestep_t* stepArray;
	DDFzoom* zoomArray;

}; extern DDFreader DDF;

#endif /* LIBRARIES_DDFREADER_DDFREADER_H_ */
