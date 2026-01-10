//Ultrasonic Sensor HC-SR04 and Arduino Tutorial
//by Dejan Nedelkovski,
//www.HowToMechatronics.com

#include <Wire.h>
#include <Tiny4kOLED.h>
//#include "5x5_font.h"
//const DCfont *currentFont = FONT5X5;
#include "pzim3x5_font.h"
const DCfont *currentFont = FONTPZIM3X5;

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distanceCm, distanceInch;

uint8_t currentCharacter;

void setup() {
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  // Prints the distance on the oled Monitor
  oled.setCursor (0,0);
  oled.print("Dist: ");
  oled.print(distanceCm); // Prints the distance value from the sensor
  oled.print(" cm");
  delay(10);
  oled.setCursor(0, 1);
  oled.print("Dist: ");
  oled.print(distanceInch);
  oled.print(" in");
  delay(10);
}