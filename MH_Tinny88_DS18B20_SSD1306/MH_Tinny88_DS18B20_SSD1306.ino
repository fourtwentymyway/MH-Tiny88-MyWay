#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
//#include "5x5_font.h"
#include "pzim3x5_font.h"

//const DCfont *currentFont = FONT5X5;
const DCfont *currentFont = FONTPZIM3X5;

#define ONE_WIRE_BUS 3

OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire);

void setup(){
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.setSpacing(currentFont->spacing + 1); //3x5Font Uncomment For 5x5FONT
  oled.clear();
  oled.on(); 
  sensors.begin();
}

void loop(void){ 
  // Choose Either Fahrenheit or Celsius With 5x5FONT //
          /////Fahrenheit/////
  //oled.setCursor(15, 0); //5x5FONT
  oled.setCursor(22, 0);
  oled.print("Degrees");
  //oled.setCursor(4, 1);  //5x5FONT
  //oled.print("Fahrenheit:");  //5x5FONT
  //oled.setCursor(15, 3);  //5x5FONT
  oled.setCursor(22, 2);
  oled.print(sensors.getTempFByIndex(0));
  //oled.setCursor(48, 3);  //5x5FONT
  oled.println(" °F");
           /////Celcius/////
  //oled.setCursor(15, 0);  //5x5FONT
  //oled.print("Degrees");  //5x5FONT
  //oled.setCursor(15, 1);  //5x5FONT
  //oled.print("Celcius:");  //5x5FONT
  oled.setCursor(22, 3);  
  oled.print(sensors.getTempCByIndex(0));
  //oled.setCursor(48, 3);  //5x5FONT
  oled.println(" °C");

}
