#include "C_Mode.h"
#include "LED.h"
#include "Schalter.h"
#include <Arduino.h>
#include <FreqCounter.h> //s.o.

C_Mode::C_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc, Schalter* schalterpin,int freq = 1){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
  this->schalter = schalterpin;
  this->freq = freq;
  this->avgNumber = max(1,6/(this->freq*2));
}

void C_Mode::start(){
  
    // c (ASCII d99)-Kontinuierlicher Betrieb mit CSV-Ausgabe
      // Mittelwert aus drei ADC-Messungen
      // ******************************************************
      // Normaler Modus
      // ******************************************************
      // LEDs richten
      this->blaueLED->setState(false);
      //digitalWrite(Ledrot,true);
      long cyclus = 0;
      //Dummy Counter-Messung, weil sonst erstes Zaehlergebnis viel zu hoch ist (16 bit)
      FreqCounter::start(20);
      
      while (FreqCounter::f_ready == 0) {
      }// warten bis der  Counter fertig ist
      
      long counts = FreqCounter::f_freq;
      
      //Dummy Wandler-Messung
      this->adc->getValue();
      this->adc->getValue();
      
      FreqCounter::start(1000/this->freq);
      
      // hier warten wir, bis wir einen wechsel auf load und dann auf inject erhalten haben
      if(schalter->schalter_modus){
        while(schalter->isInject()){
          if(this->sollAbbrechen()){
                this->abbrechen=true;
                break;
              }
              delay(100);
          }
        while(!schalter->isInject()){
          if(this->sollAbbrechen()){
                this->abbrechen=true;
                break;
              }
              delay(100);
          }
      }

      // ************************************************************************
      // Hauptmess-Schleife durchlaufen, bis ein kleines "x" gesendet wird
      while (!this->abbrechen) {
        // while (Serial.available()==0) {
        if (this->sollAbbrechen()) {
          this->abbrechen=true;
        }
        
      while (FreqCounter::f_ready == 0) {
      }// warten bis der  Counter fertig ist        

        //rote LED einschalten
        this->roteLED->setState(false);
        //blaue LED einschalten
        //digitalWrite(Ledblau,true);
        // Counterergebnis zwischenspeichern und Counter erneut starten
        counts = FreqCounter::f_freq;
        FreqCounter::start(1000/this->freq);
        // In der Zwischenzeit den Wandler aktivieren
        
        
        cyclus = cyclus + 1;
        float zeit = float(cyclus) / 60/this->freq;
        //Ergebnis übertragen
        Serial.print (cyclus);
        Serial.print (",");
        Serial.print (zeit, 3);
        Serial.print (",");
        Serial.print ((this->adc->getXAVG(this->avgNumber) * this->adc->W_Faktor), 0);
        Serial.print (",");
        Serial.print (counts, DEC);
        Serial.print ("\n");
        Serial.flush();//vollständige messreihe schicken
        this->roteLED->setState(true);

        if(schalter->schalter_modus){
          if(schalter->isLoad()){
            while(!schalter->isInject()){
              if(this->sollAbbrechen()){
                this->abbrechen=true;
                break;
              }
              delay(100);
            }
            cyclus=0;
          }
        }
		    
      }  // solange kein Zeichen gesendet wird, diese Schleife durchlaufen, danach kommt dann:
      
      //LED Signale definieren
      this->roteLED->setState(false);
      this->blaueLED->setState(false);
}

bool C_Mode::sollAbbrechen(){
    if (Serial.available() > 0) {
          // lese das empfangene Zeichen:
          // nur kleines x (ASCII d120) beendet diesen Modus
          char incomingByte = Serial.read();
          if (incomingByte == 'x') {
            return true;
          }
    }
    return false;
}







