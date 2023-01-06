/*
 * DDF file reader example
 * reads DDF file from sd card
 *
 *
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    5       CS
 *    23      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    18      SCK
 *    VSS      GND
 *    19       MISO
 *    D1       -
 * 
 * Tests: 
 */

#include "Arduino.h"
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <DDFreader.h>

#define PIN_SPI_SCK 18
#define PIN_SPI_MISO 19
#define PIN_SPI_MOSI 23
#define PIN_SPI_CSSD 5

TinyXML xml;
uint8_t buffer[DDFBUFSIZE];
void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen );


void setup(){

	SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI);	//begin SPI
	Serial.begin(115200);

	/*** XML/DDF stuff initialize etc. ***/
	xml.init((uint8_t*)&buffer, DDFBUFSIZE, XML_callback);	
	DDFreader _reader(&xml);	//initialize DDFreader
	DDF.init();
	

}

void loop(){

	DDF.readDDF("Generic Generic Dimmer + RGB (8-Bit).xml");

	Serial.println("Test done");
	while (1);
}


void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen ){	//callback fot XML

	DDFreader* instance;
	instance->XMLcallback(statusflags,tagName, tagNameLen, data, dataLen);
}