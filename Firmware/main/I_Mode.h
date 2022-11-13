#include "LED.h"
#include "RunMode.h"
#ifndef __I_MODE_INCLUDED__
#define __I_MODE_INCLUDED__
class I_Mode : public RunMode{
  public:
    I_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



