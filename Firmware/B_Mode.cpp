#include "B_Mode.h"
#include "LED.h"
#include "LTC2400.h"
#include <FreqCounter.h> //s.o.

#include <Arduino.h>


B_Mode::B_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
  
}

void B_Mode::start(){
      // b (ASCII d98) BinÃƒÂ¤rausgabe - alter Modus
      // nur aus kompatiblitÃƒÂ¤tsgrÃƒÂ¼nden zu alten Interfaces enthalten

      this->blaueLED->setState(true);
      this->roteLED->setState(false);
      
      //Dummy Messung, weil sonst erstes Zaehlergebnis viel zu hoch ist (16 bit)
      FreqCounter::start(5);

      while (FreqCounter::f_ready == 0) {
      }// warten bis der  Counter fertig ist
      
      long counts = FreqCounter::f_freq;
      FreqCounter::start(500);
      this->adc->getValue(); //   Wandlerprogrogramm aufrufen
      
      while (FreqCounter::f_ready == 0) {
      }// warten bis der  Counter fertig ist
      
      counts = FreqCounter::f_freq;
      Serial.print("<");
      Serial.print(char(this->adc->getSIG()));
      Serial.print(char(this->adc->getWandler_high()));
      Serial.print(char(this->adc->getWandler_mid()));
      Serial.print(char(this->adc->getWandler_low()));
      Serial.print("*");
      //Counter_uhigh = (byte )((n >> 24) & 0xff); //32 bit Counter mÃƒÂ¶glich! -aber wohl nicht sehr sinnvoll
      long Counter_high  = (byte )((counts >> 16) & 0xff);
      long Counter_mid   = (byte )((counts >> 8) & 0xff);
      long Counter_low   = (byte ) (counts & 0xff);
      Serial.print(char(Counter_high));
      Serial.print(char(Counter_mid));
      Serial.print(char(Counter_low));
      Serial.print(">");
      //LED Signale definieren
      blaueLED->setState(false);
      roteLED->setState(true);
 
    
}








