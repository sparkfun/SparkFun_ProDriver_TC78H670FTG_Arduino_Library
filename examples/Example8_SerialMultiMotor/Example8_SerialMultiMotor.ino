/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example controls two separate ProDrivers using Serial mode and individual LATCH pins.
  When using Serial Mode, we can share all of the control pins with many ProDrivers,
  But each ProDriver will need it's own unique latch pin.
  Before calling .begin(), we will set the latch pin as needed.
  
  Things to note:
    - Every control pin is shared EXCEPT latch (aka mode1Pin), so we must ensure all latches are low during
      ANY instances call to begin().
    - only full step (aka 1:1) control is supported via serial mode. No microstepping.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/16836

  Hardware Connections:

  ARDUINO --> PRODRIVERs
  D8 --> STBY   PRODRIVER1 and PRODRIVER2
  D7 --> EN     PRODRIVER1 and PRODRIVER2
  D6 --> MODE0  PRODRIVER1 and PRODRIVER2
  D5 --> MODE1  ***PRODRIVER1 only***       (LATCH PIN 1)
  D4 --> MODE2  PRODRIVER1 and PRODRIVER2
  D3 --> MODE3  PRODRIVER1 and PRODRIVER2
  D2 --> ERR    PRODRIVER1 and PRODRIVER2

  ARDUINO --> PRODRIVER2
  D9 --> MODE2 ***PRODRIVER2 onlyl***       (LATCH PIN 2)


*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver1; //Create instance of this object
PRODRIVER myProDriver2;
#define myProDriver2LatchPin 9

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 8");

  // myProDriver2
  // Note, this must be setup first because of shared lines.
  myProDriver2.settings.controlMode = PRODRIVER_MODE_SERIAL;
  myProDriver2.settings.mode1Pin = myProDriver2LatchPin; // latch pin
  myProDriver2.begin(); // calling this first ensure latch pin 2 will be low during other future .begin()s

  // myProDriver1
  // default latch pin is D5, so no need to change here
  myProDriver1.settings.controlMode = PRODRIVER_MODE_SERIAL;
  myProDriver1.begin();
}

void loop() {
  myProDriver1.stepSerial(200, 0); // turn 200 steps, CW direction
  delay(1000);
  myProDriver2.stepSerial(200, 0); // turn 200 steps, CW direction
  delay(1000);
}
