#include <MFRC522Extended.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <require_cpp11.h>

#define SDAPIN 10
#define RESETPIN 8
#define LED 4

byte foundTag;
byte readTag;
byte tagData[MAX_LEN];
byte tagSerialNumber[5];
byte correctTagSerialNumber = {0x22, 0x23, 0x15, 0xD};

MFRC522 nfc(SDAPIN, RESETPIN);

void setup() {
  SPI.begin(); // Serial communication
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.println("Recherche du module RFID");
  nfc.begin();
  byte version = nfc.getFirmwareVersion(); // Check for the firmware version 

  if(!version) {
    Serial.print("Module RFID non trouvé");
    while(1); // Wait until we find the module 
  }
  Serial.print("Module RFID trouvé");
  Serial.print("Version du Firmware: 0x");
  Serial.println(version, HEX);
  Serial.println();
}
