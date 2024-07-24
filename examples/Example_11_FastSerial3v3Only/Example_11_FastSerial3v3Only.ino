/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 24th, 2024
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example controls the ProDriver using "Fast Serial Mode". This mode should
  only be used when using 3.3V logic. This mode is faster than the default
  serial mode but is not compatible with 5V logic. It has to do with the 
  on-board pullups to 3.3V logic on the ProDriver.

  See github issue discussion for more information:
  https://github.com/sparkfun/SparkFun_ProDriver_TC78H670FTG_Arduino_Library/issues/2

  This example will turn a stepper motor 200 steps in one direction, pause for
  a second, then turn 200 steps in the opposite direction.

  It uses non-default pins for the ProDriver control pins. This is to show how
  to use the library with custom pin assignments.

  The pins chosen are arbitrary and can be changed to any digital pin on the
  Arduino.

  The pins chosen here are useful with the SparkFun Thing Plus - ESP32 WROOM C
  https://www.sparkfun.com/products/20168

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/16836

  Example Non-Default Hardware Connections:

  ARDUINO (3.3V) --> PRODRIVER
  14  --> STBY
  32  --> EN
  15  --> MODE0
  33  --> MODE1
  27  --> MODE2
  12  --> MODE3
  4   --> ERR (must be interrupt capable pin)
*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 11");

  // Let's setup some non-default pins to use!
  // Note, to setup any non-default settings, you much do this before you call .begin()
  myProDriver.settings.standbyPin = 14;
  myProDriver.settings.enablePin = 32;
  myProDriver.settings.mode0Pin = 15;
  myProDriver.settings.mode1Pin = 33;
  myProDriver.settings.mode2Pin = 27;
  myProDriver.settings.mode3Pin = 12;
  myProDriver.settings.errorPin = 4; // must be interrupt capable pin

  myProDriver.settings.controlMode = PRODRIVER_MODE_SERIAL; // non-default mode must be set here

  // Enable fast serial mode (only use with 3.3V logic). 
  // This will speed up the serial communication to the ProDriver
  myProDriver.settings.fastSerialMode = true; // enable fast serial mode

  myProDriver.begin(); // custom pins defined above
}

void loop() {
  myProDriver.stepSerial(200, 0, 4); // turn 200 steps, CW direction, 4ms delay in between steps
  delay(1000);
  myProDriver.stepSerial(200, 1, 4); // turn 200 steps, CCW direction, , 4ms delay in between steps
  delay(1000);
}