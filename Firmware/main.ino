/*
  Dirk Bier
  Einstieg in das AD-Counter-HPLC Projekt am 15.12.11
  Wandlerprogramm 29.12.11
  Counter integriert 30.12.11
  LED - Funktionen integriert, Hauptmenue 01.03.2013
  Counterproblem vorlaeufig geloest und einige LED Funktionenergaenzt 04.03.2013
  Wandleransteuerung verbessert 05.03.2013
  BinÃƒÂ¤rmodus integriert und einige Bugs behoben 06.03.2013
  wesentliche Aenderungen und Bug-Fixes, Code aufgrÃƒÂ¤umt und getestet 08.03.2013
  nur kleines x (AsCII 120) beendet diesen kontinuierlichen Modus 19.03.13
  Kleinigkeiten und Modus c Mittelwert aus drei Messungen 20.03.2014
  einige Ãƒâ€žnderungen q-Modus jetzt CSV, LED-Logik, d-Modus, alle Zeilenenden im Unix-Format (\n)
  Schalterabfrage fÃƒÂ¼r den Injectblock integriert und getestet 10.02.2015
  Bug in Schalterabfrage behoben 11.03.2015
  Schalterpin geÃƒÂ¤ndert auf PIN 11 + 12 RelaisausgÃƒÂ¤nge hinzugefÃƒÂ¼gt. Der Schalter liegt auf Pin 11  am 28.04.2017
  einige Bugfixes und neuer InfoString und Test o.k. am 18.05.2017
  Schaltermodi eingefÃƒÂ¼hrt - aktuelle Schalterfunktion kann abgefragt (m, ASCII 109) und kann ein und ausgeschaltet werden (t, ASCII 116)
  Schalterfunktion getestet und o.k. 19.05.20117
  Schalterfunktion ÃƒÂ¼berdacht, geÃƒÂ¤ndert und getestet: Default ist Neustart durch Load/Inject - kann aber abgeschaltet werden 19.05.2017
  Es ist jetzt auch abfragbar, ob das Injektionsventil umgelegt worden ist, auch wenn sich das Programm nicht im Messmodus befindet (ASCII y). Implementiert und getestet am 19.02.2018
 *************************************************************************************************************************
  Arduino Umgebung: 1.6.13
  FreqCounter von http://interface.khm.de/index.php/lab/experiments/arduino-frequency-counter-library/ 1/2012 ; Arduino 1.0
 *************************************************************************************************************************
*/


#include <FreqCounter.h> //s.o.
#include "LED.h"
#include "LTC2400.h"

#include "RunMode.h"
#include "B_Mode.h"
#include "C_Mode.h"
#include "D_Mode.h"
#include "H_Mode.h"
#include "I_Mode.h"
#include "Q_Mode.h"
#include "S_Mode.h"
#include "Schalter.h"

// Hardware
// ********
// ********
// LTC2400
// =======
byte Clock = 8;
byte CS = 6;
byte SDO = 7;

//LEDs
//====
byte Ledrot = 10;
byte Ledblau = 9;

//Schalter am Einspritzbock (optional)
//====================================
byte schalterPin = 11;

//Relais
//======
//byte Relais_1=12;
//byte Relais_2=13;


int incomingByte = 0;	// Empfang an Serieller Schittstelle
int freq = 0; // frequenz in Hz
LED* roteLED = 0;
LED* blaueLED = 0;
LTC2400* adConverter = 0;
RunMode* currentMode = 0;
Schalter* schalter = 0;

//****************************************************************************************
//****************************************************************************************
void setup() {
  // Wandlerleitungen definieren
  adConverter = new LTC2400(Clock,CS,SDO);
  
  // LEDs auf dem Shield
  roteLED = new LED(Ledrot, false);
  blaueLED = new LED(Ledblau, true);
  
  schalter = new Schalter(schalterPin);
  
  // Serielle Schnittstelle oeffnen
  Serial.begin(9600);
  
  // LED-toggeln signalisiert das Ãƒâ€“ffnen der Schnittstelle
  // Die blaue LED leuchtet nach dem Ende der Schleife
  digitalWrite(Ledblau, true);
  
  for (int i = 0; i <= 11; i++) {
    blaueLED->toggle();
    roteLED->toggle();
    delay(50);
  }

}
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************
void loop() {
  //blaue LED einschlaten aus Bereitschaftssignal
  if (blaueLED->getState() == false) {
    blaueLED->setState(true);
    roteLED->setState(false);
    }

    
  if (Serial.available() > 0) {
    // lese das empfangene Zeichen:
    incomingByte = Serial.read();
    
    switch(incomingByte){
      case 'h':
        currentMode = new H_Mode(roteLED,blaueLED,adConverter);
        break;
      case 'd':
        currentMode = new D_Mode(roteLED,blaueLED,adConverter);
        break;
      case 'i':
        currentMode = new I_Mode(roteLED, blaueLED,adConverter);
        break;
      case 'b':
        currentMode = new B_Mode(roteLED, blaueLED, adConverter);
        break;
      case 's':
        currentMode = new S_Mode(roteLED, blaueLED, adConverter);
        break;
      case 'c':
        currentMode = new C_Mode(roteLED, blaueLED, adConverter, schalter,1);
        break;
      case 'C':
        freq = Serial.parseInt();
        currentMode = new C_Mode(roteLED, blaueLED, adConverter, schalter,freq);
        break;
      case 'q':
        currentMode = new Q_Mode(roteLED, blaueLED, adConverter);
        break;
      case 'm':
        if (schalter->schalter_modus == true) Serial.print ("s");
        if (schalter->schalter_modus == false) Serial.print ("m");
        break;
      case 't':
        schalter->schalter_modus=!schalter->schalter_modus;
        if (schalter->schalter_modus == true) Serial.print ("s");
        if (schalter->schalter_modus == false) Serial.print ("m");
        break;
      case 'x':
        //bei x wollen wir nichts zurück schicken, sondern nur, falls vorhanden, den aktuellen modus beenden
        break;
      default:
        currentMode = new I_Mode(roteLED, blaueLED,adConverter);
        break;
    }

    if(currentMode != 0){
      currentMode->start();
      delete currentMode;
    }
    
    
    //**************************************************************************

  } // Ende Tastaturabfrage

}   // Ende Hauptschleife



