#include <Tiny4kOLED.h>
#include <TinyI2CMaster.h>
#include "pzim3x5_font.h" // Install TinyOLED-Fonts Library



void setup() {

  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(FONTPZIM3X5);
  oled.setSpacing(FONTPZIM3X5->spacing + 1); // Fixes 3x5 Font Spacing
  oled.clear();
  oled.on();
  oled.setCursor(0, 0);
  oled.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa");
}

void loop() {

}
