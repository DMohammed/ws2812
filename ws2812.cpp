
#include <Arduino.h>
#include <ws2812.h>

WS2812::WS2812()
{
}

void WS2812::begin(uint8_t pin, uint8_t numberled)
{
    // set pin as output
    //   volatile uint32_t *CRX;
    // #define port_addr GPIOC //   pin string is connected to
    //   uint8_t port_bit = 13;

    //   if (port_bit < 8)
    //     CRX = ((volatile uint32_t *)(port_addr + 0x00)); // GPIOx_CRL
    //   else
    //   {
    //     CRX = ((volatile uint32_t *)(port_addr + 0x04)); // GPIOx_CRH
    //     port_bit -= 8;
    //   }
    // *CRX &= ~(0xF << port_bit * 4); // CNF  = 0 (gp push-pull output)
    // *CRX |= 1 << port_bit * 4;      // MODE = 1 (output mode 10 MHz)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
    Serial.begin(115200);
    //
    // GPIOC->CRL = 0x33333333;
    pinMode(pin, OUTPUT);
    GPIOC->CRH = 0x33333333;
}

void WS2812::setLedColor(uint8_t numberLED, uint8_t blue, uint8_t green, uint8_t red)
{
    buffer[(numberLED * 3) + 0] = green;
    buffer[(numberLED * 3) + 1] = red;
    buffer[(numberLED * 3) + 2] = blue;
}

void WS2812::showLED()
{
    for (int i = 0; i < sizeof(buffer); i++)
    {
        k++;
        for (uint8_t j = 0; j < 8; j++)
        {
            if (bitRead(buffer[i], j) == 1)
            {
                one();
            }
            else
                zero();
        }
        if (k == 3)
        {
            clear();
            k = 0;
        }
    }
}

void WS2812::zero()
{
    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < (10))
        GPIOC->BSRR = 8192;

    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < (20))
        GPIOC->BRR = 8192;
}
void WS2812::one()
{
    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < (20))
        GPIOC->BSRR = 8192;

    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < (10))
        GPIOC->BRR = 8192;
}
void WS2812::clear()
{
    DWT->CYCCNT = 0;
    while (DWT->CYCCNT < (10))
        GPIOC->BRR = 8192;
    // GPIOC->BSRR = 8192;
}