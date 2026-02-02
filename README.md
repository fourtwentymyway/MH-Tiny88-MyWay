Arduino and Some Attiny85 Examples With Tiny4kOLED , GyverOLED & PDQ_ST7735/PDQ_GFX .
![IMG_E0160](https://github.com/user-attachments/assets/7c73278d-77a5-414c-88d7-ae99d4414843)

!!!ATTinyCore Is Used For This Board Instead Of MH-ET Live Or Most Examples Wont Work!!!
Latest Arduino IDE And Libraries Were Used .

Arduino Nano Pins Are Used Most Of the Time , Port Pins Will Be Used Sometimes Like PB1 , PC2 , PD3...ETC

Sometimes This Helps : 

#include "ATtinySerialOut.hpp"  //Arduino library "ATtinySerialOut". Saves 128 bytes program memory.
(Use "ATtinySerialOut" With CH340 (I Used ESP PROG ) RX is Pin 7 and TX is Pin 6 For Serial Monitor Instead Of OLED/TFT.)

#include <TinyI2CMaster.h>    //Samaller Wire.h Library For Tiny4KOLED.

#define USE_MICRO_WIRE       //Use With GyverOLED Sometimes Lowers Sketch Size.

![IMG_E0161](https://github.com/user-attachments/assets/ffae6846-9636-45ea-9621-6d14f3dd726b)


