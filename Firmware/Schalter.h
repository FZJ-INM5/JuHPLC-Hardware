#ifndef __SCHALTER_INCLUDED__
#define __SCHALTER_INCLUDED__
class Schalter{
  
  private:
    int pin;
  	bool schalter_inject = true;
  	bool schalter_war_load = false;
  	bool trigger = false;
    void setTrigger();

    
  public:
    Schalter(int pin);
	  Schalter* update();
    bool getStatus();
	  void reset();
	  bool getStatusFromPin();
    bool isLoad();
    bool isInject();
    bool schalter_modus = true;
    bool getTrigger();
    void resetTrigger();
};
#endif



