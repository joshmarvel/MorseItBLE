//Morse-it Bluetooth Hardware Key
//GND is common for the key
//Pin A0 is Dit
//Pin A1 is Dah
//Pin A2 is DitDah
//All commands sent are the defaults for the Morse-it app
#define MY_DEBUG 0
#include "BluefruitRoutines.h"
 
//Pin numbers for switches
#define DIT A0
#define DAH A1
#define DITDAH A2
 
//Actions
#define DO_DIT 1
#define DO_DAH   2
#define DO_DITDAH     4
 
uint8_t readSwitches(void) {
  return (~(digitalRead(DIT)*DO_DIT
      + digitalRead(DAH)*DO_DAH
      + digitalRead (DITDAH)*DO_DITDAH)
     ) & (DO_DIT+ DO_DAH+ DO_DITDAH);
}
 
//Translate character to keyboard keycode and transmit
void pressKeyCode (byte c) {
  ble.print(F("AT+BLEKEYBOARDCODE=00-00-"));
  if (c<0x10)ble.print("0");
  ble.print(c,HEX);
  ble.println(F("-00-00-00-00"));
  MESSAGE(F("Pressed."));
  delay(50);//de-bounce
  while (readSwitches()) { //wait for button to be released
    /*do nothing*/
  };
  ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
  MESSAGE(F("Released"));
}
 
void setup() {
#if(MY_DEBUG)
  while (! Serial) {}; delay (500);
  Serial.begin(9600); Serial.println("Debug output");
#endif
  pinMode(DAH, INPUT_PULLUP);
  pinMode(DITDAH, INPUT_PULLUP);
  pinMode(DIT, INPUT_PULLUP);
  initializeBluefruit();
}
 
void loop() {
  uint8_t i=readSwitches();
  switch (i) {
    case DO_DIT: pressKeyCode(0x50); break;
    case DO_DAH:   pressKeyCode(0x4F); break;
    case DO_DITDAH:     pressKeyCode(0x52); break;
  }
}
