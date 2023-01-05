/*	LC1 playground
 *
 *	Example: creating an array of DDF functions to store in an device object
 *	v1.0
 *
 *
 */
#include "Arduino.h"
#include <DDFreader.h>
//#include <tinyXML.h>

void createNewDDFdevice();

void setup(){
	Serial.begin(115200);

	int numberOfFunctions = 2;	//2 funtions
	String model = "model no1";
	String vendor = "supervendor 123";
	String author = "C.W.";


	/**** create pointer objects to generic functions ****/

	  // Two new objects
	DDFfunction<DDFdimmer>* ptr_dimmer = new DDFfunction<DDFdimmer>();	//pointer to dimmer
	DDFfunction<DDFrgb>* ptr_rgb = new DDFfunction<DDFrgb>();

	AbstractDDFfunction* ptr_arr[numberOfFunctions];	//function array

	  ptr_arr[0] = ptr_dimmer;
	  ptr_arr[1] = ptr_rgb;

	/**** create objects directly ****/
	DDFdimmer oneDimmer;
	oneDimmer.dmxchannel = 6;
	// ...

	DDFrgb oneRGB;
	oneRGB.redDmxchannel = 2;
	oneRGB.greenDmxchannel = 3;
	oneRGB.blueDmxchannel = 4;
	// ...


	ptr_arr[0]->Set(oneDimmer);	//write dimmer to functionArray
	ptr_arr[1]->Set(oneRGB);


/*** read from array ***/
	DDFdimmer anotherDimmer;

	ptr_arr[0]->Get(&anotherDimmer);

	Serial.print("new dimmer object dmxchannel:");Serial.println(anotherDimmer.dmxchannel);
	createNewDDFdevice();


}

// The loop function is called in an endless loop
void loop()
{
	// empty
}


void createNewDDFdevice(){	//create dummy device with 2x dimmer and 2x rgb
	String model = "model no1";
	String vendor = "supervendor 123";
	String author = "C.W.";


	uint16_t dimmerAmount = 2;
	uint16_t rgbAmount = 2;

	DDFdimmer firstDimmer, secondDimmer;
	firstDimmer.dmxchannel = 5;
	firstDimmer.dmxchannel = 9;

	DDFrgb firstRGB, secondRGB;
	firstRGB.redDmxchannel = 2;
	firstRGB.greenDmxchannel = 3;
	firstRGB.blueDmxchannel = 4;

	secondRGB.redDmxchannel = 6;
	secondRGB.greenDmxchannel = 7;
	secondRGB.blueDmxchannel = 8;

	DDFrgb rgbArray[rgbAmount] = {firstRGB, secondRGB};
	DDFdimmer dimmerArray[dimmerAmount] = {firstDimmer, secondDimmer};

	DDFrgbs rgbs = DDFrgbs(rgbArray,rgbAmount );	//object with all rgbs in it
	DDFdimmers dimmers = DDFdimmers(dimmerArray, dimmerAmount);	//object wich all dimmers in it

	DDFdevice newDDF(model, vendor, author, dimmerAmount, rgbAmount, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	newDDF.addDimmer(firstDimmer, 0);
	newDDF.addDimmer(secondDimmer, 1);
	newDDF.addRgb(firstRGB, 0);
	newDDF.addRgb(secondRGB, 1);

	newDDF.print();
//
//	return newDDF;
}







