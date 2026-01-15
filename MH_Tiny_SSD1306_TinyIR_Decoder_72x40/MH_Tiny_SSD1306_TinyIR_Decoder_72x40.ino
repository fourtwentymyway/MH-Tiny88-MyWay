/*
 *  TinyReceiver.cpp
 *
 *  Small memory footprint and no timer usage!
 *
 *  ***************
 */
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include <Arduino.h>
///TinyOLED-Fonts Lib///
#include "5x5_font.h"
#include "zxpix_font.h"
const DCfont *currentFont3 = FONTZXPIX;
const DCfont *currentFont = FONT5X5;

uint8_t width = 72;
uint8_t height = 40;

#  if defined(__AVR_ATtiny88__) && defined(PIN_PD3) // MH-ET Tiny88 board. For use with ATTinyCore.
#include "ATtinySerialOut.hpp" // Available as Arduino library "ATtinySerialOut". Saves 128 bytes program memory.
// Pin 6 is TX, pin 7 is RX
#define IR_RECEIVE_PIN   PIN_PD3 // 3 - INT1
#define IR_SEND_PIN      PIN_PD4 // 4
#define TONE_PIN         PIN_PB1 // 9
#define _IR_TIMING_TEST_PIN PIN_PB0 // 8

#    endif

#if !defined (FLASHEND)
#define FLASHEND 0xFFFF 
#endif


#if !defined(STR_HELPER) && !defined(STR)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

//Protocol selection

//#define DISABLE_PARITY_CHECKS // Disable parity checks. Saves 48 bytes of program memory.
#define USE_EXTENDED_NEC_PROTOCOL // Like NEC, but take the 16 bit address as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_ONKYO_PROTOCOL    // Like NEC, but take the 16 bit address and command each as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_FAST_PROTOCOL     // Use FAST protocol instead of NEC / ONKYO.
//#define ENABLE_NEC2_REPEATS // Instead of sending / receiving the NEC special repeat code, send / receive the original frame for repeat.

//#define DISABLE_PARITY_CHECKS // Disable parity checks. Saves 48 bytes of program memory.
//#define USE_CALLBACK_FOR_TINY_RECEIVER  // Call the user provided function "void handleReceivedTinyIRData()" each time a frame or repeat is received.

#include "TinyIRReceiver.hpp" 


#if !defined(STR_HELPER) && !defined(STR)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

void setup() {
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(FONT8X16);
  oled.clear();
  drawScreen();
  oled.on(); 
  oled.setCursor(11, 1);
  oled.print("TinyIR");

    // Enables the interrupt generation on change of IR input signal
    if (!initPCIInterruptForTinyReceiver()); {
        
    }


delay(5000);
oled.clear();

}

void drawScreen() {
  // Set entire memory to hatched - if you see any of this hatching, then the display is not initialised correctly.
  for (uint8_t y = 0; y < 8; y++) {
    oled.setCursor(0, y);
    oled.startData();
    for (uint8_t x=0; x<128; x += 2) {
      oled.sendData(0b10101010);
      oled.sendData(0b01010101);
    }
    oled.endData();
  }

  oled.setCursor(0, 0);
  oled.startData();
  oled.sendData(0b11111111);
  oled.repeatData(0b00000001, width - 2);
  oled.sendData(0b11111111);
  oled.endData();

  for (uint8_t y = 1; y < (height - 8) / 8; y++) {
    oled.setCursor(0, y);
    oled.startData();
    oled.sendData(0b11111111);
    oled.repeatData(0b00000000, width - 2);
    oled.sendData(0b11111111);
    oled.endData();
  }

  oled.setCursor(0, (height - 8) / 8);
  oled.startData();
  oled.sendData(0b11111111);
  oled.repeatData(0b10000000, width - 2);
  oled.sendData(0b11111111);
  oled.endData();
  
  }

void loop() {
    
    oled.setFont(currentFont);
    oled.setCursor(15, 0);
    if (TinyReceiverDecode()) {

#if !defined(USE_FAST_PROTOCOL)
        // We have no address at FAST protocol
    oled.print("Address");
    oled.setCursor(18, 1);
    oled.print(F("0x"));
    oled.print(TinyIRReceiverData.Address, HEX);
#endif
    oled.setCursor(0, 3);
    oled.print(F("Command=0x"));
    oled.print(TinyIRReceiverData.Command, HEX);
    
    oled.setCursor(13, 4);
if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
    oled.print(F(" Repeat"));
    

    }

    delay(3000);    
    oled.clear();
    }
    
}

/*
 * Optional code, if you require a callback
 */
#if defined(USE_CALLBACK_FOR_TINY_RECEIVER)
/*
 * This is the function, which is called if a complete frame was received
 * It runs in an ISR context with interrupts enabled, so functions like delay() etc. should work here
 */

}
#endif

