Arduino and Some Attiny85 Examples With Tiny4kOLED & PDQ_ST7785/PDQ_GFX .

!!!ATTinyCore Or megaTinyCore Is Used For This Board Instead Of MH-ET Live Or Most Examples Wont Work!!!
Latest Arduino IDE And Libraries Were Used .

Sometimes This Helps : #include "ATtinySerialOut.hpp"  //Arduino library "ATtinySerialOut". Saves 128 bytes program memory.
Use "ATtinySerialOut" With CH340 (I Used ESP PROG ) RX is Pin 7 and TX is Pin 6 For Serial Monitor Instead Of OLED/TFT.

Arduino Nano Pins Are Used Most Of the Time , Port Pins Will Be Used Sometimes Like PB1 , PC2 , PD3...ETC

