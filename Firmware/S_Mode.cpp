#include "S_Mode.h"
#include "LED.h"
#include <Arduino.h>
#include <FreqCounter.h> //s.o.

S_Mode::S_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
}

void S_Mode::start(){
    // s (ASCII d115) "speed" Zeitmessung fÃƒÂ¼r 10 Wandlungen in ms
    // LED Signale definieren
    blaueLED->setState(false);
    roteLED->setState(true);
    Serial.print("ADC-Zeitmessung\n");
    Serial.print("***************\n");
    Serial.print('\n');
    long t_time = millis();
    for (int i = 1; i <= 10; i++) {
      this->adc->getValue();
    }
    t_time = millis() - t_time;
    Serial.print("Zeit fuer 10 Messungen: ");
    Serial.print(t_time, DEC);
    Serial.print("  ms\n");
    float mps = 10000 / t_time;
    Serial.print(mps, 1);
    Serial.print(" Messungen pro Sekunde\n");
    Serial.println();
    //LED Signale definieren
    this->blaueLED->setState(true);
    this->roteLED->setState(false);
 
    
}







