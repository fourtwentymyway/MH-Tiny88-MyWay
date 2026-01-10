/*
 *  TinyReceiver.cpp
 *
 *  Small memory footprint and no timer usage!
 *
 *  ***************
 */
#include <PDQ_GFX.h>				// PDQ: Core graphics library
#include "PDQ_ST7735_config.h"			// PDQ: ST7735 pins and other setup for this sketch
#include <PDQ_ST7735.h>			// PDQ: Hardware-specific driver library
PDQ_ST7735 tft;			// PQ: create LCD object (using pins in "PDQ_ST7735_config.h")
#define LCD_BACKLIGHT_PIN 25
#include <Arduino.h>

#  if defined(__AVR_ATtiny88__) && defined(PIN_PD3) // MH-ET Tiny88 board. For use with ATTinyCore.
#include "ATtinySerialOut.hpp" // Available as Arduino library "ATtinySerialOut". Saves 128 bytes program memory.
// Pin 6 is TX, pin 7 is RX
#define IR_RECEIVE_PIN   PIN_PD3 // 3 - INT1
#define IR_SEND_PIN      PIN_PD4 // 4
#define TONE_PIN         PIN_PB1 // 9
#define _IR_TIMING_TEST_PIN PIN_PB0 // 8

#    endif

#if !defined (FLASHEND)
#define FLASHEND 0xFFFF // Dummy value for platforms where FLASHEND is not defined
#endif

/*
 * Helper macro for getting a macro definition as string
 */
#if !defined(STR_HELPER) && !defined(STR)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif



//#define DEBUG // to see if attachInterrupt is used
//#define TRACE // to see the state of the ISR state machine

/*
 * Protocol selection
 */
//#define DISABLE_PARITY_CHECKS // Disable parity checks. Saves 48 bytes of program memory.
#define USE_EXTENDED_NEC_PROTOCOL // Like NEC, but take the 16 bit address as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_ONKYO_PROTOCOL    // Like NEC, but take the 16 bit address and command each as one 16 bit value and not as 8 bit normal and 8 bit inverted value.
//#define USE_FAST_PROTOCOL     // Use FAST protocol instead of NEC / ONKYO.
//#define ENABLE_NEC2_REPEATS // Instead of sending / receiving the NEC special repeat code, send / receive the original frame for repeat.
/*
 * Set compile options to modify the generated code.
 */
//#define DISABLE_PARITY_CHECKS // Disable parity checks. Saves 48 bytes of program memory.
//#define USE_CALLBACK_FOR_TINY_RECEIVER  // Call the user provided function "void handleReceivedTinyIRData()" each time a frame or repeat is received.

#include "TinyIRReceiver.hpp" // include the code

/*
 * Helper macro for getting a macro definition as string
 */
#if !defined(STR_HELPER) && !defined(STR)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

void setup() {
    tft.begin();
    pinMode(LCD_BACKLIGHT_PIN, OUTPUT); // ---1.8 Screen--- Set the pin as an output
    digitalWrite(LCD_BACKLIGHT_PIN, HIGH); //---1.8 Screen--- Turn the backlight ON (HIGH is typically ON)
    // For brightness control, you would use analogWrite(LCD_BACKLIGHT_PIN, value);

    
    tft.fillScreen(ST7735_BLUE);
    tft.setTextColor(ST7735_MAGENTA);
    tft.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TINYIR));

    // Enables the interrupt generation on change of IR input signal
    if (!initPCIInterruptForTinyReceiver()) {
        tft.println(F("No interrupt available for pin " STR(IR_RECEIVE_PIN))); 
    }
#if defined(USE_FAST_PROTOCOL)
    tft.println(F("Ready to receive Fast IR signals at pin " STR(IR_RECEIVE_PIN)));
#else
    tft.println(F("Ready to receive NEC IR signals at pin " STR(IR_RECEIVE_PIN)));
#endif

delay(3000);
tft.fillScreen(ST7735_BLUE);
}

void loop() {
    
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(22, 70);
    if (TinyReceiverDecode()) {

#if !defined(USE_FAST_PROTOCOL)
        // We have no address at FAST protocol
        tft.print(F("Address=0x"));
        tft.print(TinyIRReceiverData.Address, HEX);
        
#endif
        tft.setCursor(28, 90);
        tft.print(F("Command=0x"));
        tft.print(TinyIRReceiverData.Command, HEX);
        tft.setCursor(38, 100);
        if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
            tft.print(F(" Repeat"));
        }
        if (TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED) {
            tft.print(F(" Parity failed"));

#if !defined(USE_EXTENDED_NEC_PROTOCOL) && !defined(USE_ONKYO_PROTOCOL)
            tft.print(F(", try USE_EXTENDED_NEC_PROTOCOL or USE_ONKYO_PROTOCOL"));
#endif

        }
    delay(3000);    
    tft.fillScreen(ST7735_BLUE);
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

