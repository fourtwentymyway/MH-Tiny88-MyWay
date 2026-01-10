#include <PDQ_GFX.h>				// PDQ: Core graphics library
#include "PDQ_ST7735_config.h"			// PDQ: ST7735 pins and other setup for this sketch
#include <PDQ_ST7735.h>			// PDQ: Hardware-specific driver library

PDQ_ST7735 tft;			// PDQ: create LCD object (using pins in "PDQ_ST7735_config.h")
const int trigPin = 9;
const int echoPin = 8;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  tft.begin();
	tft.setRotation(3);
  tft.invertDisplay(1);
	tft.fillScreen(ST7735_BLUE);
};

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Distance in cm = time / 58
  int distance = duration / 58;
  tft.fillRect(55, 46, 50, 25, ST7735_BLUE);  // Needed To Clear Screen Digits
	tft.setCursor(65, 50);
	tft.setTextSize(2);
	tft.setTextColor(ST7735_YELLOW);
  tft.print(distance);
  tft.println("  CM");
  tft.print("   Distance: ");
  delay(500);
}