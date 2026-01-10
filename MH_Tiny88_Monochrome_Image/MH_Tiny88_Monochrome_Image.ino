

#include <Tiny4kOLED.h>
//#include <Wire.h>
#include <TinyI2CMaster.h>
#include "image.h"
//#include "pzim3x5_font.h"
//const DCfont *currentFont = FONTPZIM3X5;
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;
void setup() {
  // put your setup code here, to run once:
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
}

void loop() {
  
  // put your main code here, to run repeatedly:
  oled.fill(0xFF); //fill screen with color
  delay(1000);
  oled.clear(); //all black
  delay(1000);
  //usage: oled.setCursor(X IN PIXELS, Y IN ROWS OF 8 PIXELS STARTING WITH 0);
  oled.setCursor(0, 0); //top left
  oled.setFont(currentFont);
  oled.print(F("420MyWay")); //wrap strings in F() to save RAM!
  oled.setFont(currentFont);
  oled.print(F(" Tiny4kOLED!"));
  oled.setCursor(0, 2); //two rows down because the 8x16 font takes two rows of 8
  oled.println(F("4k")); //println will move the cursor 8 or 16 pixels down (based on the front) and back to X=0
  
  
  delay(3000);
  //usage oled.bitmap(START X IN PIXELS, START Y IN ROWS OF 8 PIXELS, END X IN PIXELS, END Y IN ROWS OF 8 PIXELS, IMAGE ARRAY);

  delay(3000);
  oled.bitmap(0, 0, 72, 8, image);
  delay(3000);
}