#include <Tiny4kOLED.h>
#include <Wire.h>
#include "tama_mini02_font.h"
const DCfont *currentFont = FONTTAMAMINI02;



#define switch  1
unsigned int i = 0;

void setup()
{
  
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on();
  oled.setCursor(30, 6);
  oled.print("ATtiny88");
  oled.setFont(currentFont);
  oled.setCursor(7, 0);
  oled.print("420MyWay");
  oled.clear();
  pinMode(switch,INPUT);
} 

void loop()
{   
  if(digitalRead(switch) == LOW) {delay(100); i++;}
  
 
  oled.setFont(currentFont);
  oled.setCursor(0, 3);
  oled.print("#: ");
  oled.setCursor(70, 3);
  oled.println(i);
  delay(200);
}
