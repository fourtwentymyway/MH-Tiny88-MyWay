#include <PDQ_GFX.h>				// PDQ: Core graphics library
#include "PDQ_ST7735_config.h"			// PDQ: ST7735 pins and other setup for this sketch
#include <PDQ_ST7735.h>			// PDQ: Hardware-specific driver library
PDQ_ST7735 tft;			// PDQ: create LCD object (using pins in "PDQ_ST7735_config.h")
#include <TinyDHT.h>
#define DHTPIN 25
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  tft.begin();
	tft.setRotation(3);
  tft.invertDisplay(1);
	tft.fillScreen(ST7735_BLUE);
  dht.begin();
};
//// !!!CHOOSE EITHER TEMP OR HUMIDITY!!! CANT CHOOSE BOTH !!!
void loop() {
  int8_t h = dht.readHumidity();  
//  int16_t t = dht.readTemperature();

  tft.fillRect(52, 46, 27, 25, ST7735_BLUE);  // Needed To Clear Screen Digits
	tft.setCursor(55, 50);
	tft.setTextSize(2);
	tft.setTextColor(ST7735_YELLOW);

  ///UNCOMMENT FOR HUMIDITY
	tft.print(h);      // Print the value to the Serial Monitor
  tft.println(" %\t");
	tft.print("   Humidity: ");

	////UNCOMMENT FOR TEMP

//	tft.print(t);      // Print the value to the Serial Monitor
//  tft.println(" *C");
//	tft.print(" Temperature: ");	
	delay(500);                       // Wait for half a second
}

