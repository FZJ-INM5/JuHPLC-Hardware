#ifndef __LTC2400_INCLUDED__
#define __LTC2400_INCLUDED__
class LTC2400 {
  public:
    LTC2400(int clockPin, int csPin, int sdoPin);
    long getValue();
    float getXAVG(int numberOfMeasurements);

    
    static constexpr const int precisionBits = 24;
    static constexpr const float voltage = 5.0;

    static constexpr const float W_Faktor = (float)((voltage*(long)1000*(long)1000)/(long)((long)2<<((long)precisionBits-1)));//0.298023242 µVolt/Bit

    unsigned char getWandler_high();
    unsigned char getWandler_mid();
    unsigned char getWandler_low();

    unsigned char getEOC();
    unsigned char getSIG();
    unsigned char getEXR();
    unsigned char getDMY();
    
    
  private:
    int clockPin;
    int csPin;
    int sdoPin;
    void tick(int pin);
    // Globale Variablen
    // LTC2400
    unsigned char EOC = 0;
    unsigned char SIG = 0;
    unsigned char EXR = 0;
    unsigned char DMY = 0;
    
    unsigned char Wandler_high = 0;
    unsigned char Wandler_mid = 0;
    unsigned char Wandler_low = 0;
    
    unsigned long adc;
    long adc_long;

};
#endif


