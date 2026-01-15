/*
 *  TinyReceiver.cpp
 *
 *  Small memory footprint and no timer usage!
 *
 *  ***************
 */
#include <GyverOLED.h>
#define USE_MICRO_WIRE
#include <Arduino.h>

//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

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
    oled.init(); 
    oled.clear();
    oled.setScale(1);
    oled.setCursor(0, 0);
    oled.autoPrintln(true);
    oled.invertDisplay(true);
    oled.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TINYIR));

    // Enables the interrupt generation on change of IR input signal
    if (!initPCIInterruptForTinyReceiver()) {
        oled.println(F("No interrupt available for pin " STR(IR_RECEIVE_PIN))); 
    }
#if defined(USE_FAST_PROTOCOL)
    oled.println(F("Ready to receive Fast IR signals at pin " STR(IR_RECEIVE_PIN)));
#else
    oled.println(F("Ready to receive NEC IR signals at pin " STR(IR_RECEIVE_PIN)));
#endif

delay(8000);
oled.clear();
}

void loop() {
    oled.invertDisplay(false);
    oled.setScale(1);
    oled.setCursor(20, 3);
    if (TinyReceiverDecode()) {

#if !defined(USE_FAST_PROTOCOL)
        // We have no address at FAST protocol
    oled.print(F("Address=0x"));
    oled.print(TinyIRReceiverData.Address, HEX);
#endif
    oled.setCursor(25, 4);
    oled.print(F("Command=0x"));
    oled.print(TinyIRReceiverData.Command, HEX);
    oled.fastLineH(63, 0, 123);
    oled.setCursor(35, 5);
if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
    oled.print(F(" Repeat"));
    oled.fastLineH(63, 0, 123);
    }
 if (TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED) {
    oled.print(F(" Parity failed"));

#if !defined(USE_EXTENDED_NEC_PROTOCOL) && !defined(USE_ONKYO_PROTOCOL)
    oled.print(F(", try USE_EXTENDED_NEC_PROTOCOL or USE_ONKYO_PROTOCOL"));
#endif

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

