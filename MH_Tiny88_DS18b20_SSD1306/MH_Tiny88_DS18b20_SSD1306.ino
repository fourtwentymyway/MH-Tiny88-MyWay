#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(){
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
  sensors.begin();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  oled.setCursor(15, 0);
  oled.print("degrees");
  oled.setCursor(4, 1);
  oled.print("fahrenheit:");
  oled.setCursor(15, 3);
  oled.println(sensors.getTempFByIndex(0));
  oled.setCursor(48, 3);
  oled.print("°F");
  /////Celcius////
  //oled.setCursor(15, 0);
  //oled.print("degrees");
  //oled.setCursor(15, 1);
  //oled.print("celcius:");
  //oled.setCursor(15, 3);
  //Serial.print(sensors.getTempCByIndex(0));
  //oled.setCursor(48, 3);
  //oled.print("°C");
  delay(1000);
  oled.clear();
}