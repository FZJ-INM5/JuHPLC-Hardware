#include "I_Mode.h"
#include "LED.h"
#include <Arduino.h>
#include <FreqCounter.h> //s.o.

I_Mode::I_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
}

void I_Mode::start(){

  // i (ASCII d105)- Informationsstring senden
  // rote LED fÃƒÂ¼r die Zeit des seriellen Datentrasfers einschalten
  
  blaueLED->setState(false);
  roteLED->setState(true);
  
  Serial.print ("Code:AI1!ADC:LTC2400!Typ:24bit-Interface_ADC_und_Counter!Version:V18!Datum=19.05.2017/Autor:db-vm\n");
  // LED schalten - der Datentrasfer ist beendet
  
  blaueLED->setState(true);
  roteLED->setState(false);
    
}







