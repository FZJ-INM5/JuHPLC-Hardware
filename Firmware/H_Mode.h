#include "LED.h"
#include "RunMode.h"
#ifndef __H_MODE_INCLUDED__
#define __H_MODE_INCLUDED__
class H_Mode : public RunMode{
  public:
    H_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



