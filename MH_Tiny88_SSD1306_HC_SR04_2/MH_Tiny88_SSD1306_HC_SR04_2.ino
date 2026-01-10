#include <Tiny4kOLED.h>
#include "Wire.h"
int buz = 25, lamp = 0, trig = A2, echo = A3, pir = 20, jarakdeteksi;
bool state = false;

void setup() {
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.setFont(FONT6X8);
  oled.clear();
  oled.on();

  pinMode(echo, INPUT);
  pinMode(pir, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(lamp, OUTPUT);

  oled.setCursor (0,0);
  oled.print("Motion detector");
  delay (1000);
  oled.clear();

}

void loop() {
  deteksi();
  jarak(); 
}

void deteksi(){
  if (digitalRead(pir) && state && jarakdeteksi > 10){
    oled.setCursor (0,0);
    oled.print("Motion detect!!      ");

    state = false;

  } else if (!digitalRead(pir) && !state && jarakdeteksi > 10){
    oled.setCursor (0,0);
    oled.print ("No motion detect     ");
    oled.setCursor (0,1);
    oled.print ("                     ");
    oled.setCursor (0,2);
    oled.print ("                     ");
    digitalWrite(lamp, LOW);

    state = true;

  } else if (digitalRead(pir) && state && jarakdeteksi <=10){
    digitalWrite(lamp, HIGH);
    oled.setCursor(0,0);
    oled.print ("Warning, there is human detection");

    state = false;

  } else if (!digitalRead(pir) && !state || jarakdeteksi <=10){
    digitalWrite(lamp, HIGH);
    oled.setCursor(0,0);
    oled.print ("Warning, there is human detection");

    state = false;
  }
  
  if (digitalRead(lamp)==HIGH){tone(buz, 800);}
  else {noTone(buz);}
  }


void jarak(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int ping = pulseIn(echo, HIGH);
  jarakdeteksi = ping / 58;
}
