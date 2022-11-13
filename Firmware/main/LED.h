#ifndef __LED_INCLUDED__
#define __LED_INCLUDED__
class LED{
  public:
    LED(int port, bool initialState);
    void setState(bool state);
    bool getState();
    void toggle();
  private:
    int port;
    bool state;
};
#endif



