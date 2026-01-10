#include <dht.h>
//#include <Wire.h>
#include <Tiny4kOLED.h>
#include <TinyI2CMaster.h>
#define DHT11_PIN 25
#include "littleheart.h"
#include "bigheart.h"
#include "therm.h"

dht DHT;

void splash() {
  oled.clear();
  oled.setCursor(30, 1);
  oled.print(F("420MyWay"));

  oled.setCursor(25, 3);
  oled.print(F("Temp"));

  oled.setCursor(25, 5);
  oled.print(F("&"));

  oled.setCursor(25, 7);
  oled.print(F("Humidity"));
}

void heartBeat() {
  static char big = 1;
  static long startTime = 0;
  long currentTime;

  // Get current time
  currentTime = millis();

  // Update if 200ms passed
  if ((currentTime - startTime) > 200) {
    startTime = currentTime;
    big = 1 - big;

    if (big) {
      oled.bitmap(20, 4, 37, 6, img_heart_big);
    } else {
      oled.bitmap(20, 4, 37, 6, img_heart_small);
    }
  }
}

void prepareDisplay() {
  unsigned int i, k;
  unsigned char ch[5];

  oled.clear();
  oled.begin();

 // oled.setCursor(18, 0);
  //oled.print(F("Technical Shubham"));
  //led.setCursor(1, 2);
  //oled.print(F("temperature-humidity"));

  oled.bitmap(52, 0, 76, 3, img_thermometer);
  oled.setCursor(35, 4);
  oled.print(F("24.0C"));
  oled.setCursor(35, 5);
  oled.print(F("40.0%"));

  oled.bitmap(35, 5, 17, 2, img_heart_small);
}

float getTemperature() {
  return DHT.temperature;
}

float getHumidity() {
  return DHT.humidity;
}

void setup() {
  pinMode(DHT11_PIN, INPUT);

 oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);

  // Two fonts are supplied with this library, FONT8X16 and FONT6X8
  oled.setFont(FONT6X8);

  // To clear all the memory
  oled.clear();
  oled.on();

  splash();

  delay(3000);
  prepareDisplay();
}

void loop() {
  static long startTime = 0;
  long currentTime;

  DHT.read11(DHT11_PIN);

  // Get current time
  currentTime = millis();

  // Checks 1 second passed
  if ((currentTime - startTime) > 1000) {
    startTime = currentTime;
//oled.setCursor(90, 0);

    // Print to display
    
  //  oled.print("Temp & Hum");


    // Update temperature
    float temperature = getTemperature();

    // Set cursor
    oled.setCursor(90, 1);


    // Print to display
    oled.print(temperature, 1);
    oled.print("C  ");

    // Update humidity
    float humidity = getHumidity();

    // Set cursor
    oled.setCursor(90, 2);

    // Print to display
    oled.print(humidity, 1);
    oled.print("%  ");

    oled.bitmap(80, 4, 90, 7, img_thermometer);
  }

  heartBeat();
}
