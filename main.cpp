#include <Arduino.h>
#include <ws2812.h>

WS2812 led;


void setup()
{

    led.begin(PC13,6);

    led.setLedColor(0, 255,0, 0);
    led.setLedColor(1, 0, 255, 0);
    led.setLedColor(2, 0, 0, 255);
    led.setLedColor(3, 255, 0, 255);
}
void loop(){
    
}