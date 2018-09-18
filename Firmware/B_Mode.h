#include "LED.h"
#include "RunMode.h"
#ifndef __B_MODE_INCLUDED__
#define __B_MODE_INCLUDED__
class B_Mode : public RunMode{
  public:
    B_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



