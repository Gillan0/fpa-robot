#include <color.hpp>
#include <monoLightPattern.cpp> 

// Second moving pattern used by badge 1
// oldname : light4

/**
 * Spinning bicolor pattern on the NeoPixel
 * Shape : xxxo xxxo xxxo 
 * Spinning clockwise of speed 1. 
 * 
 * @param Color color1, 
 * @param Color color2, 
 * @param uint8_t frameIndex, 
 * @param Adafruit_NeoPixel &neopixel
 */
void thinBicolorLightPattern(
    Color color1, 
    Color color2, 
    uint8_t frameIndex, 
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

    monoLightPattern(
        neopixelColor1,
        neopixel
    );

    for (uint8_t i = 0; i < neopixel.numPixels() / 4; i++) {
        uint8_t ledIndex = (frameIndex + 4*i) % 12;
        neopixel.setPixelColor(ledIndex, neopixelColor2);
    }

    neopixel.show();
}