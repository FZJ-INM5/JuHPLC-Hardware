#include "Q_Mode.h"
#include "LED.h"
#include "LTC2400.h"
#include <FreqCounter.h> //s.o.
#include <Arduino.h>


Q_Mode::Q_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
  
}

void Q_Mode::start(){
      // q (ASCII d113) -Kontinuierlicher Betrieb so schnell wie mÃƒÂ¶glich binÃƒÂ¤r ohne Counter
      // LEDs richten
      // gemessen 372 Messungen / Minute = 6,2 Messungen / Sekunde
      this->blaueLED->setState(false);
      this->roteLED->setState(true);
      
      long cyclus = 0;
      //Dummy Messung
      this->adc->getValue();
      // Startzeit
      long startzeit = millis();
      //Hauptmess-Schleife durchlaufen, bis ein beliebiges Zeichen gesendet wird
      //************************************************************************
      while (Serial.available() == 0) {
         //   Wandlerprogrogramm aufrufen
        long zeit = millis();
        cyclus = cyclus + 1;
        //deltat=(zeit-startzeit)/60000;
        //((float)zeit-(float)startzeit)
        Serial.print((zeit - startzeit) / 60000, 3);
        Serial.print(',');
        Serial.print(this->adc->getValue() * this->adc->W_Faktor, 0);
        Serial.print('\n'); unsigned long time;
        //**************************************************************************
      }  // solange kein Zeichen gesendet wird, diese Schleife durchlaufen
      char incomingByte = Serial.read(); // wenn Zeichen vorhanden - dieses lesen und verwerfen
      //LEDs richten
       this->blaueLED->setState(true);
      this->roteLED->setState(false);
 
    
}







