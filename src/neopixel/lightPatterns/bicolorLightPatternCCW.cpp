#include <color.hpp>


byte base_color[] = {0,0,32, 32,32,0};

// One of the two moving patterns used by badge 2
// oldname : light3

/**
 * Spinning bicolor pattern on the NeoPixel
 * Shape : xx oo xx oo xx oo 
 * Spinning counter clockwise of speed 1. 
 * 
 * @param color1 
 * @param color1 
 * @param color1 
 * @param color1  
 */
void bicolorLightPatternCCW(
    Color color1, 
    Color color2, 
    byte frameIndex, 
    Adafruit_NeoPixel &neopixel
) {
  
    auto neopixelColor1 = neopixel.Color(
        color1.red_channel,
        color1.green_channel,
        color1.blue_channel
    );

    auto neopixelColor2 = neopixel.Color(
        color2.red_channel,
        color2.green_channel,
        color2.blue_channel
    );

    for (byte j=0;j<3;j++) {

        for (byte k=0; k < 4: k++) {
            
            
            byte ledIndex = (11 - (4*j + frameIndex + k)) % 12;
            if (k > 1) {
                neopixel.setPixelColor(ledIndex, neopixelColor1);
            } else {
                neopixel.setPixelColor(ledIndex, neopixelColor2);
            }

        } 
    }

    neopixel.show();
 
}