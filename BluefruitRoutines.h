/* This is all the blueprint specific code for all of our
 *  iOS switch control example code. We have moved it here to make
 *  the main source code more legible.
 */

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "BluefruitConfig.h"
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/* Set to 1 to factory reset and forget all paired devices.
* Make sure to set it back to one after upload, otherwise the unit
* won't remember paired devices.  Useful to keep enabled during
* testing however.
*/
#define FACTORYRESET_ENABLE 0

//Debug output routines
#if (MY_DEBUG)
  #define MESSAGE(m) Serial.println(m);
  #define FATAL(m) {MESSAGE(m); while (1);}
#else
  #define MESSAGE(m) {}
  #define FATAL(m) while (1);
#endif

void initializeBluefruit (void) {
  //Initialize Bluetooth
  if ( !ble.begin(MY_DEBUG))
  {
    FATAL(F("NO BLE?"));
  }
  if ( FACTORYRESET_ENABLE )
  {
    // Perform a factory reset
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
     FATAL(F("err: reset failed"));
  }
  }
  //Rename device
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=MorseKey" )) ) {
    FATAL(F("err:rename fail"));
  }
  //Enable HID keyboard
  if(!ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
    FATAL(F("err:enable Kb"));
  }
  if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
    FATAL(F("err: enable Kb"));
  }
  //Add or remove service requires a reset
  if (! ble.reset() ) {
    FATAL(F("err:SW reset"));
  }

}
