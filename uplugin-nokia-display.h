
#pragma once

#include <Adafruit_PCD8544.h>
#include <uPlugin.h>

class NokiaDisplay : public Adafruit_PCD8544, public uPlugin {
  bool inverted;
  uint8_t bl;

protected:
  void NokiaDisplay::drawFastText(uint8_t x, uint8_t y, const char *text);

public:
#ifdef USE_HARDWARE_SPI
  // Not specifying clk and mosi
  // enables hardware SPI mode:
  NokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst,
               uint8_t bl, bool bl_inverted)
      : Adafruit_PCD8544(dc, ce, rst), bl(bl), inverted(bl_inverted) {
#else
  NokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst,
               uint8_t bl, bool bl_inverted)
      : Adafruit_PCD8544(clk, mosi, dc, ce, rst), bl(bl),
        inverted(bl_inverted) {
#endif
    //
  }

  int NokiaDisplay::printf(uint8_t x, uint8_t y, const char *fmt, ...);

  void setup();
  void loop();
};
