#include <PDQ_GFX.h>				// PDQ: Core graphics library
#include "PDQ_ST7735_config.h"			// PDQ: ST7735 pins and other setup for this sketch
#include <PDQ_ST7735.h>			// PDQ: Hardware-specific driver library
PDQ_ST7735 tft;			// PDQ: create LCD object (using pins in "PDQ_ST7735_config.h")

// NOTE: Changes to test with Adafruit libraries (comment out PDQ lines above and un-comment the AF: ones below)

// AF: #include <Adafruit_GFX.h>		// AF: Core graphics library
// AF: #include <Adafruit_ST7735.h>		// AF: Hardware-specific library
// AF: Adafruit_ST7735 tft(10,  9, 8); 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)

extern "C" char __data_start[];		// start of SRAM data
extern "C" char _end[];			// end of SRAM data (used to check amount of SRAM this program's variables uses)
extern "C" char __data_load_end[];	// end of FLASH (used to check amount of Flash this program and static data uses)

void setup()
{
//	OSCCAL = 0xae;	// ~20MHz ATtiny overclock
	OSCCAL = 0xd0;	// ~25MHz ATtiny overclock
	OSCCAL = 0xf2;	// ~30MHz ATtiny overclock
#if defined(ST7735_RST_PIN)	// reset like Adafruit does
	FastPin<ST7735_RST_PIN>::setOutput();
	FastPin<ST7735_RST_PIN>::hi();
	FastPin<ST7735_RST_PIN>::lo();
	delay(1);
	FastPin<ST7735_RST_PIN>::hi();
#endif

	tft.begin();
	tft.fillScreen(ST7735_YELLOW);
	tft.setTextSize(0);
	tft.setTextColor(ST7735_MAGENTA);
	tft.setCursor(0, 0);
	tft.println( "Fuck You!!!" );

}

void loop() {

	
}