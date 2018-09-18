#include "LED.h"
#include "RunMode.h"
#ifndef __D_MODE_INCLUDED__
#define __D_MODE_INCLUDED__
class D_Mode : public RunMode{
  public:
    D_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



