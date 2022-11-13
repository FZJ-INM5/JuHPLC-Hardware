#include "H_Mode.h"
#include "LED.h"
#include <Arduino.h>
#include <FreqCount.h>

H_Mode::H_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc){

  this->blaueLED = blaueLED;
  this->roteLED = roteLED;
  this->adc = adc;
}

void H_Mode::start(){
  //h - Hauptmenue
  // LED Signale einstellen - Blau fÃƒÂ¼r die Zeit des seriellen Datentrasfers einschalten
  
  // blaue LED ausschalten //  rote LED einschalten
  this->blaueLED->setState(false);
  this->roteLED->setState(true);
  Serial.print('\n');
  Serial.print("Hauptmenue\n");
  Serial.print("**********\n");
  Serial.print('\n');
  Serial.print("h........dieses Menue\n");
  Serial.print("********************************************************************************************\n");
  Serial.print("b........alter Binaermodus 500 ms Countergate und einfach ADC-Messung <one Shot> - Modus\n");
  Serial.print("c........Daten in CSV-Format kontinuierlich senden, bis ein kleines x empfangen wird\n");
  Serial.print("q........ADC Daten so schnell wie moeglich hintereinander binaer senden\n");
  Serial.print("********************************************************************************************\n");
  Serial.print("i........Informationsstring senden\n");
  Serial.print("s........Ausgabe von Anzahl der ADC-Messungen pro Sekunde\n");
  Serial.print("********************************************************************************************\n");
  Serial.print("d........Debugmodus sendet alle Infos der Wandlung im CSV Format, Abbruch mit kleinem x \n");
  Serial.print("********************************************************************************************\n");
  Serial.print('\n');
  // LED Signale - der Datentrasfer ist beendet

  this->blaueLED->setState(true);
  this->roteLED->setState(false);
 
    
}







