#include <Tiny4kOLED.h>
#include "PixelOperatorBold.h"

const DCfont *currentFont = FONT8X16POB;

static uint8_t conv2d(const char *p)
{
  uint8_t v = 0;
  return (10 * (*p - '0')) + (*++p - '0');
}

static int16_t hh, mm, ss;
static unsigned long targetTime; // next action time

void setup(void)
{
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.clear();
  oled.setFont(currentFont);
  oled.on();
 
  // init LCD constant
  hh = conv2d(__TIME__);
  mm = conv2d(__TIME__ );
  ss = conv2d(__TIME__ + 6);

  targetTime = ((millis() / 1000) + 1) * 1000;

}

void loop()
{
  unsigned long cur_millis = millis();
  if (cur_millis >= targetTime)
  {
    targetTime += 1000;
    ss++; // Advance second
    if (ss == 60)
    {
      ss = 0;
      mm++; // Advance minute
      if (mm > 59)
      {
        mm = 0;
        hh++; // Advance hour
        if (hh > 23)
        {
          hh = 0;
        }
      }
    }

    // draw time
     oled.setCursor(35, 3);
    if (hh < 10) {
      oled.print('0');
    }
    oled.print(hh);
    oled.print(':');
    if (mm < 10) {
      oled.print('0');
    }
    oled.print(mm);
    oled.print(':');
    if (ss < 10) {
      oled.print('0');
    }
    oled.print(ss);
  }

  delay(1);
}
