#include "LED.h"
#include "RunMode.h"
#ifndef __Q_MODE_INCLUDED__
#define __Q_MODE_INCLUDED__
class Q_Mode : public RunMode{
  public:
    Q_Mode(LED* roteLED, LED* blaueLED, LTC2400* adc);
    void start();
};
#endif



