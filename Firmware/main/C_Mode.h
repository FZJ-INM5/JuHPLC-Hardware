#include "LED.h"
#include "RunMode.h"
#include "Schalter.h"
#ifndef __C_MODE_INCLUDED__
#define __C_MODE_INCLUDED__
class C_Mode : public RunMode{
  public:
    C_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc, Schalter* schalterpin,int freq);
    void start();
  private:
    Schalter* schalter;
    int freq; //frequenz in Hz
    int avgNumber = 3;
    bool sollAbbrechen();
    bool abbrechen=false;

};
#endif



