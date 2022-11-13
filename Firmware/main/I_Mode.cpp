#include "I_Mode.h"
#include "LED.h"
#include <Arduino.h>


I_Mode::I_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
}

void I_Mode::start(){

  // i (ASCII d105)- Informationsstring senden
  // rote LED fÃƒÂ¼r die Zeit des seriellen Datentrasfers einschalten
  
  blaueLED->setState(false);
  delay(50);
  roteLED->setState(true);
  delay(50);
  
  Serial.print ("Code:AI1!ADC:LTC2400!Typ:24bit-Interface_ADC_und_Counter!Version:V19!Datum=13.11.2022/Autor:db-vm\n");
  delay(50);
  // LED schalten - der Datentrasfer ist beendet
  
  blaueLED->setState(true);
  delay(50);
  roteLED->setState(false);
  delay(50);
    
}







