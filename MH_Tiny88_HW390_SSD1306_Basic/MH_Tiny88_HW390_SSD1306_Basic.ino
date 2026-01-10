//The Arduino reads the analog value from the sensor's Aout 
//pin using the analogRead() function. 
//This value ranges from approximately 0 (very wet) to 1023 (very dry)
#include "thermIcon.h"
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

void setup(){
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
};
void loop() {
  int sensorValue = analogRead(A0); // Read the analog value from pin A0
  oled.setFont(FONT6X8);
  oled.setCursor(13, 0);
  oled.print("Moisture");
  oled.setCursor(20, 1);
  oled.print("Level:");
  //oled.setCursor(10, 3);
  oled.bitmap(10, 0, 0, 8, image);
  oled.setCursor(28, 3);
  oled.print(sensorValue);      // Print the value to the Serial Monitor
  delay(500);                       // Wait for half a second
  oled.clear();
}
