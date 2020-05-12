//Morse-it Bluetooth Hardware Key
//GND is common for the key
//Pin A0 is Dit
//Pin A1 is Dah
//All commands sent are the defaults for the Morse-it app

#define MY_DEBUG 0
#include "BluefruitRoutines.h"
 
//Pin numbers for paddles
#define DIT A0
#define DAH A1

//Battery Monitoring and Indicating
#define VBAT A9
#define RED A3
#define GREEN A4
#define BLUE A5

//Actions
#define DO_DIT 1
#define DO_DAH 2
#define DO_DITDAH 3

//Track the state of a held switch
uint8_t held;


//Function reads the values of a pin going LOW (Pin to GND)
uint8_t readSwitches(void) {
  if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){return DO_DITDAH;}
  else if (digitalRead(DIT) == LOW){return DO_DIT;}
  else if (digitalRead(DAH) == LOW){return DO_DAH;}
  else {return false;}
}

//Function to send a release key via Bluetooth when the pin goes HIGH (Pin open)
void Drop(void) {
  ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
  MESSAGE(F("Released"));
  }

 
//Main Function, Sends key presses as BLE keyboard characters and monitors battery voltage
void pressKeyCode (byte c) {
  ble.print(F("AT+BLEKEYBOARDCODE=00-00-"));
  if (c<0x10)ble.print("0");
  ble.print(c,HEX);
  ble.println(F("-00-00-00-00"));
  MESSAGE(F("Pressed."));
  delay(50);//de-bounce
  while (readSwitches()) {
    if (held == 3){
      if (digitalRead(DIT) == HIGH){Drop();return DO_DAH;}
      else if (digitalRead(DAH) == HIGH){Drop();return DO_DIT;}
    }
    else if (held == 2){
      if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){Drop();return DO_DITDAH;}
      else if (digitalRead(DAH) == HIGH){Drop();return DO_DIT;}
    }
    else if (held == 1){
      if (digitalRead(DIT) == LOW && digitalRead(DAH) == LOW){Drop();return DO_DITDAH;}
      else if (digitalRead(DIT) == HIGH){Drop();return DO_DAH;}
    }
  };
  ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
  MESSAGE(F("Released"));

  //Battery Voltage Monitoring, Blue LED for external USB power, Green for Normal power, Red for charge needed.
  float bvolt = analogRead(VBAT);
  bvolt *= 2;
  bvolt *= 3.3;
  bvolt /= 1024;
  if (bvolt > 4.2){
    analogWrite(BLUE, 255);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
  }
  else if (bvolt <= 4.2 && bvolt >= 3.4) {
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
    analogWrite(RED, 0);
  }
  else if (bvolt < 3.4){
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
}

//Setup device and assign pinModes
void setup() {
#if(MY_DEBUG)
  while (! Serial) {}; delay (500);
  Serial.begin(9600); Serial.println("Debug output");
#endif
  pinMode(DAH, INPUT_PULLUP);
  pinMode(DIT, INPUT_PULLUP);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  initializeBluefruit();
}

//Defines the characters to be sent.
void loop() {
  held=readSwitches();
  switch (held) {
    case DO_DIT: pressKeyCode(0x50);break;  //left arrow
    case DO_DAH: pressKeyCode(0x4F);break;  //right arrow
    case DO_DITDAH: pressKeyCode(0x52);break;  //up arrow
  }
}
