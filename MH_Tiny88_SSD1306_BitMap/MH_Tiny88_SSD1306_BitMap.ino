
#include "8ball24x24.h" 
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

void setup(){
  //oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
}

void loop() {
  oled.bitmap(24,1, 48, 4, bitmap );
}
