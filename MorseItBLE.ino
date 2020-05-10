//Morse-it Bluetooth Hardware Key
//GND is common for the key
//Pin A0 is Dit
//Pin A1 is Dah
//All commands sent are the defaults for the Morse-it app
#define MY_DEBUG 0
#include "BluefruitRoutines.h"
 
//Pin numbers for switches
#define DIT A0
#define DAH A1
 
//Actions
#define DO_DIT 1
#define DO_DAH 2
#define DO_DITDAH 3

uint8_t i;

uint8_t readSwitches(void) {
  if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){return DO_DITDAH;}
  else if (digitalRead(DIT) == LOW){return DO_DIT;}
  else if (digitalRead(DAH) == LOW){return DO_DAH;}
  else {return false;}
}

void Drop(void) {
  //delay(40);
  ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
  MESSAGE(F("Released"));
  }

 
  //Translate character to keyboard keycode and transmit
void pressKeyCode (byte c) {
  ble.print(F("AT+BLEKEYBOARDCODE=00-00-"));
  if (c<0x10)ble.print("0");
  ble.print(c,HEX);
  ble.println(F("-00-00-00-00"));
  MESSAGE(F("Pressed."));
  delay(50);//de-bounce
  while (readSwitches()) {
    if (i == 3){
      if (digitalRead(DIT) == HIGH){Drop();return DO_DAH;}
      else if (digitalRead(DAH) == HIGH){Drop();return DO_DIT;}
    }
    else if (i == 2){
      if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){Drop();return DO_DITDAH;}
      else if (digitalRead(DAH) == HIGH){Drop();return DO_DIT;}
    }
    else if (i == 1){
      if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){Drop();return DO_DITDAH;}
      else if (digitalRead(DIT) == HIGH){Drop();return DO_DAH;}
    }
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
  pinMode(DIT, INPUT_PULLUP);
  initializeBluefruit();
}
 
void loop() {
  i=readSwitches();
  switch (i) {
    case DO_DIT: pressKeyCode(0x50);break;
    case DO_DAH: pressKeyCode(0x4F);break;
    case DO_DITDAH: pressKeyCode(0x52);break;
  }
}