/*
 * DDFreader.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef LIBRARIES_DDFREADER_DDFREADER_H_
#define LIBRARIES_DDFREADER_DDFREADER_H_
#include "Arduino.h"
#include <DDFcheck.h>
#include <DDF_function.h>
#include <DDFdevice.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#define DDFBUFSIZE 6000	//Bytes

#define PIN_SPI_MOSI 5
#define PIN_SPI_MISO 16
#define PIN_SPI_SCK 17
#define PIN_SPI_CSSD 18

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
public:
	DDFreader();
	void setDDFpath(String path);

	void checkFunctions(String filename);
	void readDDF(String filename);
	void readDDF(String filename, DDFdevice *device);
//	DDFdevice readDDF(String *filename);
//	deviceInformation_t readDDF(String *filename);

private:
	void getDDFInformation();	//read DDF information
	void getDDFarrays();

	DDFdimmer getDDFfuncDimmer();
	DDFdimmer getDDFfuncDimmerArray(uint16_t no);
	void getDDFfuncFocus();
	DDFposition getDDFfuncPosition();
	void getDDFfuncPtspeed();
	DDFrgb getDDFfuncRgb();
	void getDDFfuncRawstep();	//ToDo: implement
	void getDDFfuncRaw();	//ToDo: implement
	void getDDFfuncMatrix();	//ToDo: iplement
	void getDDFfuncGobo();	//ToDO: implement
	void getDDFfuncColorwheel();	//ToDo: implement

	char* _json;
	int _length;
	char ddfJson[];
	String jsonStr;

	String _ddfPath = "/";

	ddfInformation_t ddfInfo;
	deviceInformation_t deviceInfo;

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

};

#endif /* LIBRARIES_DDFREADER_DDFREADER_H_ */
