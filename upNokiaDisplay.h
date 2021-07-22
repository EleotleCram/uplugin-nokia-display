
#pragma once

#include <Adafruit_PCD8544.h>
#include <uPlugin.h>

#define ON true
#define OFF false

class upNokiaDisplay : public Adafruit_PCD8544, public uPlugin {
  bool inverted;
  uint8_t bl;

protected:
  void upNokiaDisplay::drawFastText(uint8_t x, uint8_t y, const char *text);

public:
#ifdef USE_HARDWARE_SPI
  // Not specifying clk and mosi
  // enables hardware SPI mode:
  upNokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst, uint8_t bl,
                 bool bl_inverted)
      : Adafruit_PCD8544(dc, ce, rst), bl(bl), inverted(bl_inverted) {
#else
  upNokiaDisplay(uint8_t clk, uint8_t mosi, uint8_t dc, uint8_t ce, uint8_t rst, uint8_t bl,
                 bool bl_inverted)
      : Adafruit_PCD8544(clk, mosi, dc, ce, rst), bl(bl), inverted(bl_inverted) {
#endif
    //
  }

  int printf(uint8_t x, uint8_t y, const char *fmt, ...);
  void setbl(bool on);
  bool isbl();

  void setup();
  void loop();
};
