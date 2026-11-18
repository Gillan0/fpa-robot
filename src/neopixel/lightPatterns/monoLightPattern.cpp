#include <color.hpp>

/**
 *  Flashes a monochrome light on the neopixel.
 *  Color defined through RGB parameters
 * 
 *  @param color struct representing a color 
 *  @param neopixel Adafruit_NeoPixel
 */
void monoLightPattern(
    Color color, 
    Adafruit_NeoPixel &neopixel
) {
    
    auto neopixelColor = neopixel.Color(
        color.red_channel, 
        color.green_channel, 
        color.blue_channel
    );

    for (uint16_t ledIndex = 0; ledIndex < neopixel.numPixels(); ledIndex++) {
        neopixel.setPixelColor(
            ledIndex, 
            neopixelColor
        );
    
    }
  
    neopixel.show();
}