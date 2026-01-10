
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

const int MOISTURE_ANALOGIC_IN = A0; // Arduino's analogic pin
const int BOARD_RESOLUTION = 1024; // The analogic board resolution, for example Arduino Uno is 10 bit (from 0 to 1023)
const float OPERATIONAL_VOLTAGE = 5.0; // The default Arduino voltage
const float MAX_SENSOR_VOLTAGE = 3.0; // The maximum voltage that the sensor can output
const float SENSOR_READ_RATIO = OPERATIONAL_VOLTAGE / MAX_SENSOR_VOLTAGE; // The ratio betwent the two voltages

void setup(){
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
}


void loop() {
  int moistureAnalogicVal = analogRead(MOISTURE_ANALOGIC_IN) * SENSOR_READ_RATIO; // Read the analogic data and convert it to [0, 1023] range
  
  if (moistureAnalogicVal < BOARD_RESOLUTION * 0.1) {
    oled.println("Drowned!");
  } else if (moistureAnalogicVal < BOARD_RESOLUTION * 0.33) {
    oled.println("really!");
  } else if (moistureAnalogicVal < BOARD_RESOLUTION * 0.66) {
    oled.println("It is ok!");
  } else if (moistureAnalogicVal < BOARD_RESOLUTION * 0.9) {
    oled.println("barely!");
  } else {
    oled.println("dry!");
  }
  
  delay(3000); // Wait 3 second
  oled.clear();
}