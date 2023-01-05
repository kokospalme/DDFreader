/*	LC1 playground
 *
 *	Example: creating an array of DDF functions to store in an device object
 *	v1.0
 *
 *
 */
#include "Arduino.h"
#include <DDFreader.h>
#include <tinyXML.h>



void setup(){
	Serial.begin(115200);

	int numberOfFunctions = 2;	//2 funtions
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





}

// The loop function is called in an endless loop
void loop()
{
	// empty
}
