/*
 * DDF file reader example
 * reads DDF file from sd card
 *
 *
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    18       CS
 *    5      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    17      SCK
 *    VSS      GND
 *    16       MISO
 *    D1       -
 */

#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <DDFreader.h>


void setup(){

	SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI);	//begin SPI


    Serial.begin(115200);
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
    Serial.printf("SD Card Size: %lluMB\n", cardSize);


    //read generic Dimmer + RGB-file
    String filename = "Generic Generic Dimmer + RGB (8-Bit).json";
    DDFreader ddf;
    ddf.readDDF(&filename);


}

void loop(){

}
