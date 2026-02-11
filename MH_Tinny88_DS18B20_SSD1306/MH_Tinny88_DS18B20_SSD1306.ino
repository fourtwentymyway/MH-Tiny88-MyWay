#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"
const DCfont *currentFont = FONT5X5;

#define ONE_WIRE_BUS_1 3


OneWire oneWire_in(ONE_WIRE_BUS_1);


DallasTemperature sensor_inhouse(&oneWire_in);


void setup(void)
{
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
  oled.setCursor(17, 2);
  oled.println("DS18B20");
  sensor_inhouse.begin();
  delay(800);
  oled.clear();
}

void loop(void)
{
  oled.setFont(currentFont);
  sensor_inhouse.requestTemperatures();
  oled.setCursor(15, 0);
  oled.print("degrees");
  oled.setCursor(4, 1);
  oled.print("fahrenheit:");
  oled.setCursor(17, 3);
  oled.println(sensor_inhouse.getTempFByIndex(0));
       /////Celcius/////
//   oled.setCursor(15, 0);
//   oled.print("degrees");
//   oled.setCursor(15, 1);
//   oled.print("celcius:");
//   oled.setCursor(13, 3);
//   oled.print(sensor_inhouse.getTempCByIndex(0));
 }