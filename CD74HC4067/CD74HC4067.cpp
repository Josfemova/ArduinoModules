#include "CD74HC4067.h"
CD74HC4067::CD74HC4067(pin_t s0, pin_t s1, pin_t s2, pin_t s3, pin_t commonIO):
    s0{s0},
    s1{s1},
    s2{s2},
    s3{s3},
    commonIO{commonIO}{
}

bool CD74HC4067::begin()
{
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    channel(Y0);
}
int CD74HC4067::digitalReadMux(MuxChannel x){
    channel(x);
    return digitalRead(commonIO);
}

int CD74HC4067::analogReadMux(MuxChannel x){
    channel(x);
    return analogRead(commonIO);
}

void CD74HC4067::digitalWriteMux(MuxChannel x, byte value){
    channel(x);
    if(value!=LOW)
        digitalWrite(commonIO, HIGH);
    else
        digitalWrite(commonIO,LOW);

}

void CD74HC4067::analogWriteMux(MuxChannel x, int value){
    channel(x);
    analogWrite(commonIO,value);
}