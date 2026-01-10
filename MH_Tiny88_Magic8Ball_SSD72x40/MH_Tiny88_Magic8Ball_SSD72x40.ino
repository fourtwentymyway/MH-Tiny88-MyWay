#include "8ball24x24.h"
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "5x5_font.h"

const DCfont *currentFont = FONT5X5;

// set up a constant for the tilt switch pin
const int switchPin = 6;

// variable to hold the value of the switch pin
int switchState = 0;

// variable to hold previous value of the switch pin
int prevSwitchState = 0;

// a variable to choose which reply from the crystal ball
int reply;

void setup(){
  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(currentFont);
  oled.clear();
  oled.on(); 

  // set up the switch pin as an input
  pinMode(switchPin, INPUT);

  // Print a message to the oled.
  oled.bitmap(24,1, 48, 4, bitmap );
  oled.setCursor(15, 0);
  oled.print("Ask the");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  oled.setCursor(20, 4);
  // print to the second line
  oled.print("magic");

}

void loop() {
  // check the status of the switch
  switchState = digitalRead(switchPin);

  // compare the switchState to its previous state
  if (switchState != prevSwitchState) {
    // if the state has changed from HIGH to LOW you know that the ball has been
    // tilted from one direction to the other
    if (switchState == LOW) {
      // randomly chose a reply
      reply = random(8);
      // clean up the screen before printing a new reply
      oled.clear();
      // set the cursor to column 0, line 0
      oled.setCursor(0, 0);
      // print some text
      oled.print("Ball    says");
      // move the cursor to the second line
      oled.bitmap(24,1, 48, 4, bitmap );
      

      // choose a saying to print based on the value in reply
      switch (reply) {
        case 0:
          oled.setCursor(28, 4);
          oled.print("Yes");
          break;

        case 1:
          oled.setCursor(3, 4);
          oled.print("Most likely");
          break;

        case 2:
          oled.setCursor(10, 4);
          oled.print("Certainly");
          break;

        case 3:
          oled.setCursor(5, 4);
          oled.print("looks good");
          break;

        case 4:
          oled.setCursor(20, 4);
          oled.print("Unsure");
          break;

        case 5:
          oled.setCursor(10, 4);
          oled.print("Ask again");
          break;

        case 6:
          oled.setCursor(10, 4);
          oled.print("Doubtful");
          break;

        case 7:
          oled.setCursor(31, 4);
          oled.print("No");
          break;
      }
    }
  }
  // save the current switch state as the last state
  prevSwitchState = switchState;
}
