//Morse-it Bluetooth Hardware Key
//THIS VERSION IS FOR iOS 14 AND NEWER ONLY.

//Pin A0 is for RED LED
//Pin A1 is for Green LED
//Pin A2 is for Blue LED
//Pin A3 is for Factory Reset
//Pin A4 is Dah
//Pin A5 is Dit
//All commands sent are the defaults for the Morse-it app

//Set debug to 1 to enable console debug messages.
#define MY_DEBUG 0

#include "BluefruitRoutines.h"

//Battery Monitoring and Indicating
#define RED A0
#define GREEN A1
#define BLUE A2
#define VBAT A9

//Pin for factory reset
#define RESET A3

//Pin numbers for paddles
#define DAH A4
#define DIT A5

//Press and hold pin A2 LOW for 2 seconds to blink LED and forget all previously paired devices and all dynamic memory
void factoryreset(void){
    //MESSAGE(F("Reset Pressed."));
    delay(2000);
    if (digitalRead(RESET) == LOW){
      delay(500);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 0);
      analogWrite(RED, 255);
      delay(500);
      analogWrite(RED, 0);
      analogWrite(BLUE, 255);
      delay(500);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 255);
      ble.factoryReset();
      ble.reset();
      analogWrite(RED, 255);
      delay(1000);
      setup();
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
  pinMode(RESET, INPUT_PULLUP);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  initializeBluefruit();
}

//Defines the characters to be sent.
void loop() {
   if (digitalRead(DIT) == LOW){
    ble.println(F("AT+BLEKEYBOARDCODE=00-00-50-00-00-00-00")); //Send left arrow key
    delay(14);  //This can be adjusted if you are experiencing issues with doubled characters or stuck characters, value is in milliseconds
    if (digitalRead(DIT) == HIGH && digitalRead(DAH) == HIGH){ //release the key
      ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
      }
    }

  if (digitalRead(DAH) == LOW){
    ble.println(F("AT+BLEKEYBOARDCODE=00-00-4F-00-00-00-00")); //Send right arrow key
    delay(14);  //This can be adjusted if you are experiencing issues with doubled characters or stuck characters, value is in milliseconds
    if (digitalRead(DIT) == HIGH && digitalRead(DAH) == HIGH){ //release the key
      ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
      }
    }

  if (digitalRead(RESET) == LOW){ //Monitors for reset button push
    factoryreset();
    }

   //Battery Voltage Monitoring, Blue LED for external USB power/Full Charge, Green for Normal power, Red for charge needed.
  float bvolt = analogRead(VBAT);
  bvolt *= 2;
  bvolt *= 3.3;
  bvolt /= 1024;
  if (bvolt > 4.1){
    analogWrite(BLUE, 255);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
  }
  else if (bvolt <= 4.1 && bvolt >= 3.7) {
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
    analogWrite(RED, 0);
  }
  else if (bvolt < 3.7){
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }
  //MESSAGE(bvolt);
}
