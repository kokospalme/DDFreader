/*
 * DDFreader.cpp
 *
 *  Created on: 30 Oct 2022
 *      Author: Chris
 */

#include "DDFreader.h"

TinyXML *DDFreader::xml;
String DDFreader:: _ddfPath = "/";
ddfInformation_t DDFreader::ddfInfo;
deviceInformation_t DDFreader::deviceInfo;

uint16_t DDFreader::colorwheelCounter;
uint16_t DDFreader::dimmerCounter = 0;
uint16_t DDFreader::focusCounter = 0;
uint16_t DDFreader::frostCounter = 0;
uint16_t DDFreader::gobowheelCounter = 0;
uint16_t DDFreader::matrixCounter = 0;
uint16_t DDFreader::positionCounter = 0;
uint16_t DDFreader::prismCounter = 0;
uint16_t DDFreader::ptspeedCounter = 0;
uint16_t DDFreader::rawCounter = 0;
uint16_t DDFreader::rgbCounter = 0;
uint16_t DDFreader::shutterCounter = 0;
uint16_t DDFreader::stepfuncCounter = 0;
uint16_t DDFreader::zoomCounter = 0;

DDFreader::DDFreader(TinyXML *xml){	//class constructor
	this->xml = xml;
}

void DDFreader::init(){
	Serial.println("initialize SD card...");

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
}

void DDFreader::setDDFpath(String path){
	if(path.endsWith("/"))_ddfPath = path;
	else path+="/";_ddfPath = path;	//add "/" if missing
}

void DDFreader::readDDF(String filename){
	String path = _ddfPath;
	path += filename;
	Serial.printf("Reading file: %s\n", path.c_str());

	File file = SD.open(path.c_str());	//open file


	if(!file){
		Serial.println("Failed to open file for reading");
		return;
	}


//filesize OK --> read charwise
	uint16_t charCounter = 0;
	uint16_t fileSize = file.size();
	Serial.println("Read from file: ");
	if(fileSize <= DDFBUFSIZE){
	char xmlBuffer[fileSize];
	while(file.available()){
		xmlBuffer[charCounter] =  file.read();
		Serial.print(xmlBuffer[charCounter]);
		charCounter++;
	}
	file.close();

	char *c = xmlBuffer;
	do {
		xml->processChar(*c);
	}  while (*c++);

	}else Serial.println("fille too big! (6000 bytes max)");
}

void DDFreader::XMLcallback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen )
{
  if (statusflags & STATUS_START_TAG)
  {
    if ( tagNameLen )
    {
      Serial.print("Start tag ");
      Serial.println(tagName);

		startTag(String(tagName));
    }
  }
  else if  (statusflags & STATUS_END_TAG)
  {
    Serial.print("End tag ");
    Serial.println(tagName);
	 Serial.println(" ");
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

void DDFreader::startTag(String tagName){
	if(tagName == )
}