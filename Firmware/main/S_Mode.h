#include "LED.h"
#include "RunMode.h"
#ifndef __S_MODE_INCLUDED__
#define __S_MODE_INCLUDED__
class S_Mode : public RunMode{
  public:
    S_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



