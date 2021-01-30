# MorseItBLE
A simple Bluetooth interface to use a hardware CW key with the Morse-it app with battery charge indication and reset functionality
### Morse-it Bluetooth Low Emissions Hardware Key
Read more over on my site: [M0WYP.com](https://m0wyp.com/2020/05/08/morse-it-ble-hardware-cw-key/)

### New in Version 2
#### For iOS version 14 or greater only
Get [version 1.0](https://github.com/joshmarvel/MorseItBLE/releases/tag/V1.0) for older iOS versions.
Utilizes iOS 14's ability to repeat a key hold and therefore eliminates the need to send the up arrow.  This should solve a great number of timing issues in the previous version.  However, if you find that there are timing errors (this seems to be related to various types of Apple hardware), make adjustments to the delay lines 72 and 80 in MorseItBLE.ino.


#### This project utilizes (at minimum):

1. An iOS device with Bluetooth LE capabilities
2. [Morse-it](https://apps.apple.com/us/app/morse-it/id284942940)
3. [Adafruit Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829)
4. And a physical CW key of your choice.
5. Various bits of wire and a micro USB cable
6. Soldering iron and solder, wire strippers and other basic electronics tools.

#### Procedure
1. Update the firmware on Feather
   1. Easiest way is to download [BlueFruit Connect](https://apps.apple.com/us/app/bluefruit-connect/id830125974)
   2. Open the app, find the "Adafruit Bluefruit LE" device and click the "Connect" button
   3. Scroll down the list, find the "Update" menu option and install the latest firmware
2. Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software)
3. Follow the [Adafruit Arduino setup](https://learn.adafruit.com/adafruit-arduino-ide-setup) guide to add the Adafruit boards to the IDE.
4. Connect the board to the computer with a micro USB cable
5. Create new project in the Arduino IDE
6. Copy the 3 files from the project into your new project.
7. Compile the project
8. Upload the project to the board
9. Wire the CW key to the board
   1. GND - Common on the CW key
   2. PIN A0 - Red LED
   3. PIN A1 - Green LED
   4. PIN A2 - Blue LED
   5. PIN A3 - RESET button
   6. PIN A4 - Dah(_) for iambic keys
   7. PIN A5 - Dit(.) for iambic keys or both for straight keys
10. On your iOS device, go to "Settings" -> "Bluetooth" and discover "MorseKey"
11. Open Morse-it, go the "Tap" tab and test sending.


#### A huge thanks to the work done by Chris Young on his [tutorials](https://learn.adafruit.com/ios-switch-control-using-ble) and [GitHub page](https://github.com/cyborg5/iOS_switch_control/).  This project is adapted and modified from his original work and is licensed under [Creative Commons ShareALike](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode).
