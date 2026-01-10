
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

const int BUTTON_PIN = 6; 
const int RELAY_PIN  = 3; 

void setup() {
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(RELAY_PIN, OUTPUT);        
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); 

  if (buttonState == LOW) {
    oled.clear();
    oled.setCursor(30,2);
    oled.println("ON");
    digitalWrite(RELAY_PIN, HIGH); 
    
  }
  else
  if (buttonState == HIGH) {
    oled.clear();
    oled.setCursor(30,2);
    oled.println("OFF");
    digitalWrite(RELAY_PIN, LOW);  
    
  }
}
