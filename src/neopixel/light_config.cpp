#include <Adafruit_NeoPixel.h>    
#include <stdlib.h>


#define PIN_NEOPIXEL = 2;         // Arduino Pin connected to Neopixel
#define LED_NB_NEOPIXEL = 12;     // Number of LEDs on Neopixel


// Generator for the Neopixel
Adafruit_NeoPixel setup_neopixel() {
    neopixel = Adafruit_NeoPixel(
        LED_NB_NEOPIXEL, 
        PIN_NEOPIXEL, 
        NEO_GRB + NEO_KHZ800
    );

    return neopixel;
}