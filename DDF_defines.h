/*
 * DDFdefines.h
 *
 *  Created on: 27 Oct 2022
 *      Author: Chris
 */

#ifndef DDF_DEFINES_H_
#define DDF_DEFINES_H_
#include <Arduino.h>
#include "DDFrgb.h"

#define FNCID_NONE -1
#define FNCID_COLORWHEEL 0
#define FNCID_COLORWHEEL_STEP 22
#define FNCID_COLORWHEEL_ROTATION 23
#define FNCID_DIMMER 1
#define FNCID_FOCUS 2
#define FNCID_FROST 3
#define FNCID_GOBOWHEEL 4
#define FNCID_MATRIX 5
#define FNCID_POSITION 6
#define FNCID_POSITION_PAN 7
#define FNCID_POSITION_TILT 8
#define FNCID_PRISM 9
#define FNCID_PTSPEED 10
#define FNCID_RAW 11
#define FNCID_RGB 12
#define FNCID_RGB_R 13
#define FNCID_RGB_G 14
#define FNCID_RGB_B 15
#define FNCID_RGB_W 16
#define FNCID_RGB_A 17
#define FNCID_RGB_UV 18
#define FNCID_SHUTTER 19
#define FNCID_STEP 20
#define FNCID_ZOOM 21

#define DDFBUFSIZE 2000	//Bytes
#define DDFBUFFERSIZE_SAFETY 150 	//bytes safety (next line must not exceed this size)

#define PIN_SPI_MOSI 23
#define PIN_SPI_MISO 19
#define PIN_SPI_SCK 18
#define PIN_SPI_CSSD 5

/* XML TAGS */
#define TAG_DEVICE "/device"
#define ATTRIBUTE_DEVICETYPE "type"
#define ATTRIBUTE_DMXCVERSION "dmxcversion"
#define ATTRIBUTE_DDFVERSION "ddfversion"

#define TAG_INFO_LIBID "/device/information/ddf-library-id"
#define TAG_INFO_MODEL "/device/information/model"
#define TAG_INFO_VENDOR "/device/information/vendor"
#define TAG_INFO_AUTHOR "/device/information/author"
#define TAG_INFO_MODE "/device/information/mode"
#define TAG_INO_ELECTRICAL "/device/information/electrical"
#define TAG_INO_ELECTRICAL_STATIC "/device/information/electrical/static"
#define TAG_INO_ELECTRICAL_dimmer "/device/information/electrical/dimmer"

#define TAG_NONE "no Tag"
#define TAG_FUNCTIONS_COLORWHEEL "/device/functions/colorwheel"
#define TAG_FUNCTIONS_COLORWHEEL_STEP "/device/functions/colorwheel/step"
#define TAG_FUNCTIONS_COLORWHEEL_ROTATION "/device/functions/colorwheel/wheelrotation"
#define TAG_FUNCTIONS_COLORWHEEL_ROTATION_RANGE "/device/functions/colorwheel/wheelrotation/range"
#define TAG_FUNCTIONS_COLORWHEEL_RAINBOW "/device/functions/colorwheel/rainbow"
#define TAG_FUNCTIONS_COLORWHEEL_RAINBOW_STEP "/device/functions/colorwheel/rainbow/step"
#define TAG_FUNCTIONS_COLORWHEEL_RAINBOW_RANGE "/device/functions/colorwheel/rainbow/range"
#define TAG_FUNCTIONS_COLORWHEEL_RANDOM "/device/functions/colorwheel/random"
#define TAG_FUNCTIONS_COLORWHEEL_RANDOM_STEP "/device/functions/colorwheel/random/step"
#define TAG_FUNCTIONS_COLORWHEEL_RANDOM_RANGE "/device/functions/colorwheel/random/range"
#define TAG_FUNCTIONS_DIMMER "/device/functions/dimmer"
#define TAG_FUNCTIONS_FOCUS "/device/functions/focus"
#define TAG_FUNCTIONS_FROST  "/device/functions/frost"
#define TAG_FUNCTIONS_GOBOWHEEL  "/device/functions/gobowheel"
#define TAG_FUNCTIONS_GOBOWHEEL_ROTATION  "/device/functions/gobowheel/goborotation"
#define TAG_FUNCTIONS_GOBOWHEEL_STEP  "/device/functions/gobowheel/step"
#define TAG_FUNCTIONS_GOBOWHEEL_STEP_RANGE  "/device/functions/gobowheel/step/range"
#define TAG_FUNCTIONS_GOBOWHEEL_INDEX  "/device/functions/gobowheel/goboindex"
#define TAG_FUNCTIONS_GOBOWHEEL_INDEX_RANGE  "/device/functions/gobowheel/goboindex/range"
#define TAG_FUNCTIONS_MATRIX "/device/functions/matrix"
#define TAG_FUNCTIONS_POSITION "/device/functions/position"
#define TAG_FUNCTIONS_POSITION_PAN "/device/functions/position/pan"
#define TAG_FUNCTIONS_POSITION_PAN_RANGE "/device/functions/position/pan/range"
#define TAG_FUNCTIONS_POSITION_TILT "/device/functions/position/tilt"
#define TAG_FUNCTIONS_POSITION_TILT_RANGE "/device/functions/position/tilt/range"
#define TAG_FUNCTIONS_PRISM "/device/functions/prism"
#define TAG_FUNCTIONS_PTSPEED "/device/functions/ptspeed"
#define TAG_FUNCTIONS_PTSPEED_RANGE "/device/functions/ptspeed/range"
#define TAG_FUNCTIONS_RAW "/device/functions/raw"
#define TAG_FUNCTIONS_RGB "/device/functions/rgb"
#define TAG_FUNCTIONS_RGB_R "/device/functions/rgb/red"
#define TAG_FUNCTIONS_RGB_G "/device/functions/rgb/green"
#define TAG_FUNCTIONS_RGB_B "/device/functions/rgb/blue"
#define TAG_FUNCTIONS_RGB_W "/device/functions/rgb/white"
#define TAG_FUNCTIONS_RGB_A "/device/functions/rgb/amber"
#define TAG_FUNCTIONS_RGB_U "/device/functions/rgb/uv"
#define TAG_FUNCTIONS_SHUTTER "/device/functions/shutter"
#define TAG_FUNCTIONS_STEP "/device/functions/step"
#define TAG_FUNCTIONS_ZOOM "/device/functions/zoom"

#define ATTRIBUTE_DMXCHANNEL "dmxchannel"
#define ATTRIBUTE_FINEDMXCHANNEL "finedmxchannel"
#define ATTRIBUTE_RANGE "range"
#define ATTRIBUTE_TYPE "type"
#define ATTRIBUTE_VAL "val"
#define ATTRIBUTE_MINDMX "mindmx"
#define ATTRIBUTE_MAXDMX "maxdmx"
#define ATTRIBUTE_MINVAL "minval"
#define ATTRIBUTE_MAXVAL "maxval"
#define ATTRIBUTE_CAPTION "caption"

#define STEPTYPE_GOBO "gobo"
#define STEPTYPE_COLOR "color"
#define STEPTYPE_RAW "raw"

#define SHUTTERTYPE_OPEN "open"
#define SHUTTERTYPE_CLOSED "closed"
#define RANGE_LINEAR "linear"
#define STROBETYPE_PULSE "pulse"
#define STROBETYPE_RANDOM "random"
#define ROTATIONTYPE_STOP "stop"
#define ROTATIONTYPE_CLOCKWISE "cw"
#define ROTATIONTYPE_COUNTERCLOCKWISE "ccw"

#define RANDOM_TYPE_FAST "fast"
#define RANDOM_TYPE_MEDIUM "medium"
#define RANDOM_TYPE_SLOW "slow"



struct ddfInformation_t{	//struct for information about the ddf header
	int ddfLibraryId = -1;
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

struct deviceInformation_t{	//struct for information about the functional dimensions of the device
	bool readSucess = true;	//ToDo: obsolet? indicates, if the ddf is read properly

	ddfInformation_t info;	//info about ddf header (vendor, author etc...)

	uint16_t functioncount = 0;	// ToDo: obsolet, da funktionen in "DDFdevice" Objekt gespeichert? amount of functions

	int colorwheelCount = 0;	//number of colorwheels
	int singlecolorCount = 0;	//number of singlecolors in current wheel
	int colorCount = 0;	//number of colors in total (all colorwheels)
	int dimmerCount = 0;	//number of dimmers
	int focusCount = 0;
	int frostCount = 0;
	int gobowheelCount = 0;
	int singlegoboCount = 0;
	int matrixCount = 0;
	int positionCount = 0;
	int prismCount = 0;
	int ptspeedCount = 0;
	int rawCount = 0;
	int rgbCount = 0;
	int shutterCount = 0;
	int stepfuncCount = 0;
	int singlestepCount = 0;
	int zoomCount = 0;

};

enum dimCurves{
	curve_linear
};

enum steptypes{
	steps_color,
	steps_gobo,
	steps_open
};

enum matrixtype{
	matrix_cartesian,
	matri_polar
};


struct singlestep_t{	//step type
	uint8_t steptype = 0;
	uint32_t val = 0;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
	uint16_t stepfuncNo = 0;
};

struct stepfunc_t{
	int dmxchannel = -1;
	uint16_t currentStep = 0;
	uint16_t stepCount = 1;	// min. 1 singlestep/ function
	uint16_t size = 1;
};

struct singlecolor_t{	//struct for details about a single color of a colorwheel
	uint16_t wheelNo = 0;
	uint32_t color = 0xFFFFFF;
	uint8_t colorR = 0xFF;
	uint8_t colorG = 0xFF;
	uint8_t colorB = 0xFF;
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
};

struct colorwheel_t{	//struct for details about a single colorwheel
	uint16_t size = 0;
	uint16_t wheelNo = 0;
	int dmxchannel = -1;	//dmx channel

	int rainbowStopMindmx = -1;	//rainbow/wheelrotation STOP
	int rainbowStopMaxdmx = -1;
	double rainbowStopMinvalue = -1;
	double rainbowStopMaxvalue = -1;

	int rainbowCwMindmx = -1;	//rainbow/wheelrotation CW
	int rainbowCwMaxdmx = -1;
	double rainbowCwMinvalue = -1;
	double rainbowCwMaxvalue = -1;

	int rainbowCCwMindmx = -1;	//rainbow/wheelrotation CCW
	int rainbowCCwMaxdmx = -1;
	double rainbowCCwMinvalue = -1;
	double rainbowCCwMaxvalue = -1;

	int randomFastMindmx = -1;	//random color
	int randomFastMaxdmx = -1;

	int randomMediumMindmx = -1;
	int randomMediumMaxdmx = -1;

	int randomSlowMindmx = -1;
	int randomSlowMaxdmx = -1;
};

struct singlegobo_t{
	String path = "empty.gif";
	uint8_t mindmx = 0;
	uint8_t maxdmx = 255;
	String caption = "empty";
	int gobowheelNo = -1;

	uint8_t shakeMindmx = 0;
	uint8_t shakeMaxdmx = 0;
	double shakeminVal = -1;
	double shakeMaxVal = -1;
};

struct gobowheel_t{
	int dmxchannel = -1;
	uint16_t currentGobo = 0;
//	uint16_t goboCount = 1;	// min. 1 gobo/wheel ToDo: obsolet?
	uint16_t size = 1;

	int rotationDmxchannel = -1;
	int rotationFinedmxchannel = -1;

	int indexDmxchannel = -1;
	int indexFinedmxchannel = -1;
	double indexRange = -1;
	uint8_t indexMindmx = -1;
	uint8_t indexMaxdmx = -1;
};

struct matrixPixel_t{
	int x_angle = -1;	//-1 = not set
	int x_distance = -1;
	DDFrgb pixel;
};

#endif /* DDF_DEFINES_H_ */
