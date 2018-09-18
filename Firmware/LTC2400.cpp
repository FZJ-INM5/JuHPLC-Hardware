#include "LTC2400.h"
#include <Arduino.h>


LTC2400::LTC2400(int clockPin, int csPin, int sdoPin){
  this->clockPin = clockPin;
  this->csPin = csPin;
  this->sdoPin = sdoPin;
  
  // Wandlerleitungen definieren
  pinMode (this->clockPin, OUTPUT);
  pinMode (this->csPin, OUTPUT);
  
  pinMode (this->sdoPin, INPUT);

  
  digitalWrite (this->csPin, HIGH);
  digitalWrite (this->clockPin, LOW);
  
}

void LTC2400::tick(int pin){
  delayMicroseconds(1);
  digitalWrite(pin, LOW);
  delayMicroseconds(1);
  digitalWrite (pin, HIGH);
  delayMicroseconds(1);
}

long LTC2400::getValue(){
  // LTC2400 24 BIT Wandler
  // Abb. 5 des Datenblatts "Single Cycle Operation"
  
 // LTC2400 24 BIT Wandler
  // Abb. 5 des Datenblatts "Single Cycle Operation"
  /*this->Signal = 1;
  digitalWrite (this->csPin, LOW);
  while (this->Signal == 1)
  {
    digitalWrite (this->csPin, LOW);
    delayMicroseconds(1);
    digitalWrite (this->csPin, HIGH);
    delayMicroseconds(1);
  }*/
  
  do{
    this->tick(this->csPin);
  }while(digitalRead(this->sdoPin));
  
  //Serial.print("Schritt 1");
  digitalWrite (this->csPin, LOW);
  delayMicroseconds(1);
  // EOC lesen
  this->tick(this->clockPin);
  this->EOC = digitalRead (this->sdoPin);
  this->tick(this->clockPin);
  this->DMY = digitalRead (this->sdoPin);
  this->tick(this->clockPin);
  this->SIG = digitalRead (this->sdoPin);
  this->tick(this->clockPin);
  this->EXR = digitalRead (this->sdoPin);
  delayMicroseconds(1);
  digitalWrite(this->clockPin, LOW);
  // 24 - Bit - Wandlerwert einlesen
  this->Wandler_high = shiftIn(this->sdoPin, this->clockPin, MSBFIRST);
  this->Wandler_mid  = shiftIn(this->sdoPin, this->clockPin, MSBFIRST);
  this->Wandler_low  = shiftIn(this->sdoPin, this->clockPin, MSBFIRST);

  
  // Messung beenden
  digitalWrite (this->clockPin, LOW);
  digitalWrite (this->csPin, HIGH);
  delayMicroseconds(1);

  
  // Berechnung der drei Ergebnis-Bytes
  if ((this->SIG == 0) && (this->EXR == 1))
  {
    this->Wandler_high = 255 - this->Wandler_high;
    this->Wandler_mid  = 255 - this->Wandler_mid;
    this->Wandler_low  = 255 - this->Wandler_low;
  }
  this->adc = ((this->Wandler_high << 8) | this->Wandler_mid << 8) | this->Wandler_low;
  
  //Umwandlung in "long" wg. Vorzeichen
  this->adc_long = this->adc;
  //Vorzeichen berÃƒÂ¼cksichtigen
  //Rohdaten des Wandlers jetzt in test_long
  if (this->SIG == 0)
  {
    this->adc_long = this->adc_long * -1;
  }

  return this->adc_long;
}

float LTC2400::getXAVG(int numberOfMeasurements){
  float tmp = 0;
  
  for(int i=0;i<numberOfMeasurements;i++){
    tmp+=this->getValue();
  }
  
  return tmp/(float)numberOfMeasurements;
}

unsigned char LTC2400::getWandler_high(){
  return this->Wandler_high;
  }
unsigned char LTC2400::getWandler_mid(){
  return this->Wandler_mid;
  }
unsigned char LTC2400::getWandler_low(){
  return this->Wandler_low;
  }

  unsigned char LTC2400::getSIG(){
  return this->SIG;
  }
unsigned char LTC2400::getEXR(){
  return this->EXR;
  }
unsigned char LTC2400::getDMY(){
  return this->DMY;
  }

    unsigned char LTC2400::getEOC(){
  return this->EOC;
  }

