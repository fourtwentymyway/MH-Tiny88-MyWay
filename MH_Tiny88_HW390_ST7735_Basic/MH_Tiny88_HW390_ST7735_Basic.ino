#include <PDQ_GFX.h>				// PDQ: Core graphics library
#include "PDQ_ST7735_config.h"			// PDQ: ST7735 pins and other setup for this sketch
#include <PDQ_ST7735.h>			// PDQ: Hardware-specific driver library
PDQ_ST7735 tft;			// PQ: create LCD object (using pins in "PDQ_ST7735_config.h")
#define LCD_BACKLIGHT_PIN 3

void setup()
{

  tft.begin();
	tft.setRotation(3);
  tft.invertDisplay(1);
	tft.fillScreen(ST7735_BLUE);
  tft.fillRect(6, 40, 150, 70, ST7735_BLACK); // X sTART,Y CENTER,  Xpx LONG, Y HEIGHT
	//digitalWrite(ST7735TFT_RST, LOW); delay(100);
  tft.setCursor(125, 20);
	tft.setTextSize(3);
	tft.setTextColor(ST7735_WHITE);
	tft.print( "    420 " );
  tft.setCursor(125, 43);
	tft.setTextSize(3);
	tft.setTextColor(ST7735_WHITE);
	tft.print( "   MyWAY " );
	delay(1000);
	tft.fillScreen(ST7735_BLUE); //Needed To Clear Screen Stop Flickering
	tft.fillRect(6, 30, 150, 70, ST7735_BLACK);
	pinMode(LCD_BACKLIGHT_PIN, OUTPUT); // Set the pin as an output
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH); // Turn the backlight ON (HIGH is typically ON)
  // For brightness control, you would use analogWrite(LCD_BACKLIGHT_PIN, value);
  
};

void loop() {
   

  int sensorValue = analogRead(A0); // Read the analog value from pin A0	
  
	tft.setCursor(125, 15);
	tft.setTextSize(3);
	tft.setTextColor(ST7735_YELLOW);
	tft.print( "  DHT 390 " );
	tft.fillRect(55, 65, 70, 22, ST7735_BLACK);  // Needed To Clear Screen Stop Flickering
	tft.setCursor(55, 65);
	tft.setTextSize(3);
	tft.setTextColor(ST7735_YELLOW);
	tft.print(sensorValue);      // Print the value to the Serial Monitor
  delay(500);                       // Wait for half a second
}

