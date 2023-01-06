/*
 * DDF file reader example (nur TinyXML)
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
#include <TinyXML.h>

#define PIN_SPI_SCK 18
#define PIN_SPI_MISO 19
#define PIN_SPI_MOSI 23
#define PIN_SPI_CSSD 5

#define FILEBUFFERSIZE 500
char filebuffer[FILEBUFFERSIZE];
uint16_t charCounter = 0;
TinyXML xml;
uint8_t buffer[FILEBUFFERSIZE];
uint16_t buflen = FILEBUFFERSIZE;
char message[] = "<obj_1><environment>Earth</environment><data><value1>5</value1><value2>11</value2></data></obj_1>";
void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen );


void setup(){

	SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI);	//begin SPI
	Serial.begin(115200);
	xml.init((uint8_t*)&buffer, buflen, &XML_callback);
	 

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

	
	//read generic Dimmer + RGB-file
	String filepath = "/Generic Generic Dimmer + RGB (8-Bit).xml";
	File file = SD.open(filepath.c_str());	
	if (file) {

	while(file.available()){
		filebuffer[charCounter] =  file.read();
		Serial.print(filebuffer[charCounter]);
		charCounter++;
	}
	file.close();
	Serial.println("\nfile was read.");
	}else{
		Serial.println("file was notread.");
	}





}

void loop(){
  char *c = filebuffer;
  do {
    xml.processChar(*c);
  }  while (*c++);

  Serial.println("Test done");
  while (1);
}


void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen )
{
  if (statusflags & STATUS_START_TAG)
  {
    if ( tagNameLen )
    {
      Serial.print("Start tag ");
      Serial.println(tagName);
    }
  }
  else if  (statusflags & STATUS_END_TAG)
  {
    Serial.print("End tag ");
    Serial.println(tagName);
  }
  else if  (statusflags & STATUS_TAG_TEXT)
  {
    Serial.print("Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
  else if  (statusflags & STATUS_ATTR_TEXT)
  {
    Serial.print("Attribute:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
  else if  (statusflags & STATUS_ERROR)
  {
    Serial.print("XML Parsing error  Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
}