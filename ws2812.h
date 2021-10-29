#ifndef WS2812_H
#define WS2812_H

#include <Arduino.h>

class WS2812
{
public:
    WS2812();
    void begin(uint8_t pin,uint8_t numberled);
    void setLedColor(uint8_t numberLED, uint8_t blue, uint8_t green, uint8_t red);
    void showLED();

private:
    void zero();
    void one();
    void clear();
    int k = 0;
    uint8_t buffer[24];///////////////////set buffer for leds///// size of buffer equal to number led*3

};

#endif
