
#pragma once

#include <uPlugin.h>
#include <Adafruit_PCD8544.h>

class NokiaDisplay : public Adafruit_PCD8544, public uPlugin {

protected:
  void NokiaDisplay::drawFastText(uint8_t x, uint8_t y, const char *text);

public:
#ifdef USE_HARDWARE_SPI
                                                                                 // Not specifying clk and mosi
                                                                                 // enables hardware SPI mode:
  NokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst) : Adafruit_PCD8544(dc, ce, rst) {
#else
  NokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst) : Adafruit_PCD8544(clk, mosi, dc, ce, rst) {
#endif
    //
  }

  int NokiaDisplay::printf(uint8_t x, uint8_t y, const char *fmt, ...);

  void setup();
  void loop();
};
