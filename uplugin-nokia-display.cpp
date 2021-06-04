
#include <every.h>

#include <uplugin-nokia-display.h>

#include "c64font.h"

void NokiaDisplay::drawFastText(uint8_t x, uint8_t y, const char *text) {
  uint8_t offset = 0;
  for (int i = 0; i < strlen(text); i++) {
    const uint8_t *data = c64font + ((text[i]) - ' ') * 9;
    const uint8_t glyph_width = pgm_read_word_near(data);

    drawBitmap(x + offset, y, data + 1, 8, 8, BLACK);
    offset += glyph_width + 1;
  }
}

int NokiaDisplay::printf(uint8_t x, uint8_t y, const char *fmt, ...) {
  va_list argv;

  va_start(argv, fmt);

  char buf[16] = {0};
  const int count = vsnprintf(buf, 16, fmt, argv);

  va_end(argv);

  drawFastText(x, y, buf);

  return count;
}

#define DEFAULT_CONTRAST 175
#define DEFAULT_BIAS 0x14

void NokiaDisplay::setup() {
  // Initialize Display
  begin(DEFAULT_CONTRAST, DEFAULT_BIAS);
}

void NokiaDisplay::loop() {
  EVERY(40 MILLISECONDS) { display(); }
}
