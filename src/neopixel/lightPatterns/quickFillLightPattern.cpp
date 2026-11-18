#include <color.hpp>

//old name : light5
void quickFillLightPattern(
    Color color, 
    uint8_t frameIndex,
    Adafruit_NeoPixel &neopixel
) {

    auto neopixelColor = pixels.Color(
        color.red_channel,
        color.green_channel,
        color.blue_channel,
    )

    for (uint8_t i = 0; i < neopixel.numPixels() / 4; i ++) {
        uint8_t ledIndex = (11 - (frameIndex + 4 * i ) % 12);
        neopixel.setPixelColor(ledIndex, neopixelColor);
    }

    neopixel.show();
}