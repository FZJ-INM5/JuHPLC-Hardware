#include "LED.h"
#include "LTC2400.h"
#ifndef __RUNMODE_INCLUDED__
#define __RUNMODE_INCLUDED__
class RunMode{
  public:
    virtual void start() = 0;
  protected:
    LED* blaueLED;
    LED* roteLED;
    LTC2400* adc;
};
#endif



