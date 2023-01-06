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

#define TAG_
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

	uint16_t colorwheelCount = 0;
	uint16_t dimmerCount = 0;
	uint16_t focusCount = 0;
	uint16_t frostCount = 0;
	uint16_t gobowheelCount = 0;
	uint16_t matrixCount = 0;
	uint16_t positionCount = 0;
	uint16_t prismCount = 0;
	uint16_t ptspeedCount = 0;
	uint16_t rawCount = 0;
	uint16_t rgbCount = 0;
	uint16_t shutterCount = 0;
	uint16_t StepCount = 0;
	uint16_t ZoomCount = 0;

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




	// void getDDFInformation();	//read DDF information
	// void getDDFarrays();

	// DDFdimmer getDDFfuncDimmer();
	// DDFdimmer getDDFfuncDimmerArray(uint16_t no);
	// void getDDFfuncFocus();
	// DDFposition getDDFfuncPosition();
	// void getDDFfuncPtspeed();
	// DDFrgb getDDFfuncRgb();
	// void getDDFfuncRawstep();	//ToDo: implement
	// void getDDFfuncRaw();	//ToDo: implement
	// void getDDFfuncMatrix();	//ToDo: iplement
	// void getDDFfuncGobo();	//ToDO: implement
	// void getDDFfuncColorwheel();	//ToDo: implement

	// int _length;	//ToDo: obsolet?
	static TinyXML *xml;

	static String _ddfPath;

	static ddfInformation_t ddfInfo;
	static deviceInformation_t deviceInfo;

	static uint16_t colorwheelCounter;
	static uint16_t dimmerCounter;
	static uint16_t focusCounter;
	static uint16_t frostCounter;
	static uint16_t gobowheelCounter;
	static uint16_t matrixCounter;
	static uint16_t positionCounter;
	static uint16_t prismCounter;
	static uint16_t ptspeedCounter;
	static uint16_t rawCounter;
	static uint16_t rgbCounter;
	static uint16_t shutterCounter;
	static uint16_t stepfuncCounter;
	static uint16_t zoomCounter;

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
