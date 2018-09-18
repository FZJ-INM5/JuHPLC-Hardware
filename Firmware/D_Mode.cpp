#include "D_Mode.h"
#include "LED.h"
#include <Arduino.h>
#include <FreqCounter.h> //s.o.

D_Mode::D_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
}

void D_Mode::start(){
  // d (ASCII d100) Kontinuierlicher Debug-Modus mit CSV-Ausgabe
      // LEDs richten
      blaueLED->setState(false);
      
      //digitalWrite(Ledrot,true);
      long cyclus = 0;
      //Dummy Counter-Messung, weil sonst erstes Zaehlergebnis viel zu hoch ist (16 bit)
      FreqCounter::start(20);

      while (FreqCounter::f_ready == 0) {
      }// warten bis der  Counter fertig ist
            
      long counts = FreqCounter::f_freq;
      //Dummy Wandler-Messung
      this->adc->getValue();
      FreqCounter::start(1000);
      //Hauptmess-Schleife durchlaufen, bis ein beliebiges Zeichen gesendet wird
      while (true) {
        //while (Serial.available()==0) {
        if (Serial.available() > 0) {
          // lese das empfangene Zeichen:
          // nur kleines x (AsCII 120) beendet diesen Modus
          char incomingByte = Serial.read();
          if (incomingByte == 'x') {
            break;
          }
        }
        
        while (FreqCounter::f_ready == 0) {
        }// warten bis der  Counter fertig ist
        
        //rote LED einschalten
        roteLED->setState(true);
        //blaue LED einschalten
        //digitalWrite(Ledblau,true);
        // Counterergebnis zwischenspeichern und Counter erneut starten
        counts = FreqCounter::f_freq;
        FreqCounter::start(1000);
                
        // Umwandlung ins Dezimalformat [Mikrovolt]
        long adc_long = this->adc->getValue();
        float mikrovolt = adc_long * this->adc->W_Faktor ;
        cyclus = cyclus + 1;
        //Ergebnis ÃƒÂ¼bertragen
        Serial.print (cyclus);
        Serial.print (",");
        float zeit = float(cyclus) / 60;
        Serial.print (zeit, 3);
        Serial.print (",");
        Serial.print (adc_long, BIN);
        Serial.print (",");
        Serial.print (adc_long);
        Serial.print (",");
        Serial.print (mikrovolt, 0);
        Serial.print (",");
        Serial.print(this->adc->getEOC(), BIN);
        Serial.print(this->adc->getDMY(), BIN);
        Serial.print(this->adc->getSIG(), BIN);
        Serial.print(this->adc->getEXR(), BIN);
        Serial.print (",");
        Serial.print (counts, BIN);
        Serial.print (",");
        Serial.print (counts, DEC);
        Serial.print ("\n");
        // LED
        roteLED->setState(false);
      }  // solange kein Zeichen gesendet wird, diese Schleife durchlaufen, danach kommt dann:
      //LED Signale definieren        //digitalWrite(Ledblau,true);        //digitalWrite(Ledblau,true);        //digitalWrite(Ledblau,true);        //digitalWrite(Ledblau,true);

      roteLED->setState(false);
      blaueLED->setState(true);
      

}







