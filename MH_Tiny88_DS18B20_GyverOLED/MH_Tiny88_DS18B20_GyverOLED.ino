#include <GyverDS18.h>
#define USE_MICRO_WIRE
#include <GyverOLED.h>
#include "ATtinySerialOut.hpp"

GyverDS18Single ds(3);  // пин
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;


void setup() {
    oled.init();
    oled.clear();
    oled.setScale(2);
    oled.setCursor(25, 3);
    oled.print("DS18B20");
    delay(3000); 
    oled.clear();
 
    ds.requestTemp(); 
}
void loop() {
float celsius = ds.getTemp(); 
float fahrenheit;
fahrenheit = (celsius * 1.8) + 32;

    oled.setScale(1);
    oled.setCursor(30, 0);
    if (ds.ready()) {         
        if (ds.readTemp()) {  
            oled.print("Temperature: ");
            oled.setCursor(45, 3);
            oled.setScale(1);
            oled.print(fahrenheit);
            oled.println(" F");
            oled.setCursor(45, 5);
            oled.setScale(1);
            oled.print(celsius);
            oled.println(" C");
        } else {
            oled.clear();
            oled.setCursor(35, 3);
            oled.println("error");
        }

        ds.requestTemp();  
        oled.update();
    }
}