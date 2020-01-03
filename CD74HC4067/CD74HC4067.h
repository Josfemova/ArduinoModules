#ifndef CD74HC4067_H
#define CD74HC4067_H
#include <Arduino.h>

typedef byte pin_t;

//available channels in IC 
enum MuxChannel : pin_t{
    Y0=0x00,
    Y1=0x01,
    Y2=0x02,
    Y3=0x03,
    Y4=0x04,
    Y5=0x05,
    Y6=0x06,
    Y7=0x07,
    Y8=0x08,
    Y9=0x09,
    Y10=0x0A,
    Y11=0x0B,
    Y12=0x0C,
    Y13=0x0D,
    Y14=0x0E,
    Y15=0x0F
};

class CD74HC4067
{
private:
    //pins for channel selection
    const pin_t s0;
    const pin_t s1;
    const pin_t s2;
    const pin_t s3;
    //labeled Z in the breakout
    const pin_t commonIO;
    void channel(MuxChannel x){
        //reading the bytes of the number
        digitalWrite(s0, ((x>>0)&0x01));
        digitalWrite(s1, ((x>>0)&0x01));
        digitalWrite(s2, ((x>>0)&0x01));
        digitalWrite(s3, ((x>>0)&0x01));

    }
public:
    CD74HC4067(pin_t s0, pin_t s1, pin_t s2, pin_t s3, pin_t commonIO);
    bool begin();
    int digitalReadMux(MuxChannel x);
    int analogReadMux(MuxChannel x);
    void digitalWriteMux(MuxChannel x, byte value);
    void analogWriteMux(MuxChannel x, int value);
};

#endif