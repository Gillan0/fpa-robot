

void rainbowLightPattern(
    uint8_t frameIndex, 
    Adafruit_NeoPixel &neopixel
) {
 
    neopixel.setPixelColor(frameIndex % 12, neopixel.Color(128*intensity,0,0));
    neopixel.setPixelColor((frameIndex + 1) % 12, neopixel.Color(98*intensity,32*intensity,0));
    neopixel.setPixelColor((frameIndex + 2) % 12, neopixel.Color(64*intensity,64*intensity,0));
    neopixel.setPixelColor((frameIndex + 3) % 12, neopixel.Color(32*intensity,98*intensity,0));
    neopixel.setPixelColor((frameIndex + 4) % 12, neopixel.Color(0,128*intensity,0));
    neopixel.setPixelColor((frameIndex + 5) % 12, neopixel.Color(0,98*intensity,32*intensity));
    neopixel.setPixelColor((frameIndex + 6) % 12, neopixel.Color(0,64*intensity,64*intensity));
    neopixel.setPixelColor((frameIndex + 7) % 12, neopixel.Color(0,32*intensity,98*intensity));
    neopixel.setPixelColor((frameIndex + 8) % 12, neopixel.Color(0,0,128*intensity));
    neopixel.setPixelColor((frameIndex + 9) % 12, neopixel.Color(32*intensity,0,98*intensity));
    neopixel.setPixelColor((frameIndex + 10) % 12, neopixel.Color(64*intensity,0,64*intensity));
    neopixel.setPixelColor((frameIndex + 11) % 12, neopixel.Color(98*intensity,0,32*intensity));
   
    neopixel.show();
}