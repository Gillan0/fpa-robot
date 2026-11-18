#include <color.hpp>
#include <monoLightPattern.cpp>

byte base_color[] = {0,0,32, 32,32,0};

// Animated pattern used when RFID badge is identified and name is shown
// oldname : light2

void userIdLightPattern(
    Color color1, 
    Color color2, 
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

    neopixel.clear();
    
    // Progression of Color2 filling all LEDs during 1500ms total
    for (byte ledIndex=0; ledIndex < 12; ledIndex++) {
        neopixel.setPixelColor(ledIndex, neopixelColor2);
        neopixel.show();
        delay(125);
    }

    // When Color2 fills all, clear for 250ms
    neopixel.clear();
    delay(250);

    // Flash Color1 for 250ms
    monoLightPattern(neopixelColor1);
    neopixel.show();
    delay(250);

}