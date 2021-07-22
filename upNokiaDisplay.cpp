
#include <every.h>

#include <upNokiaDisplay.h>

#include "c64font.h"

void upNokiaDisplay::drawFastText(uint8_t x, uint8_t y, const char *text) {
  uint8_t offset = 0;
  for (int i = 0; i < strlen(text); i++) {
    const uint8_t *data = c64font + ((text[i]) - ' ') * 9;
    const uint8_t glyph_width = pgm_read_word_near(data);

    drawBitmap(x + offset, y, data + 1, 8, 8, BLACK);
    offset += glyph_width + 1;
  }
}

int upNokiaDisplay::printf(uint8_t x, uint8_t y, const char *fmt, ...) {
  va_list argv;

  va_start(argv, fmt);

  char buf[16] = {0};
  const int count = vsnprintf(buf, 16, fmt, argv);

  va_end(argv);

  drawFastText(x, y, buf);

  return count;
}

void upNokiaDisplay::setbl(bool on) {
  digitalWrite(bl, inverted ? !on : on);
}

bool upNokiaDisplay::isbl() {
  return digitalRead(bl) != inverted;
}

#define DEFAULT_CONTRAST 175
#define DEFAULT_BIAS 0x14

void upNokiaDisplay::setup() {
  // Initialize bl
  if (inverted) {
    // We only need to logically make the signal low, for the BL leds to light on.
    pinMode(bl, INPUT_PULLUP);
  } else {
    // We must source the current to drive the BL leds.
    pinMode(bl, OUTPUT);
  }

  // Initialize Display
  begin(DEFAULT_CONTRAST, DEFAULT_BIAS);
}

void upNokiaDisplay::loop() {
  EVERY(40 MILLISECONDS) {
    display();
  }
}
