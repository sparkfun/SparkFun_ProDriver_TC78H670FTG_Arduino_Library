/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example turns the motor back and forth at different torque settings.
  Note, torque can only be adjusted while in SERIAL MODE,
  and stepSerial must be called for the torque setting change to take effect.
  
  Valid torque settings are as follows:
  PRODRIVER_TRQ_100 (default set in constructor)
  PRODRIVER_TRQ_75
  PRODRIVER_TRQ_50
  PRODRIVER_TRQ_25

  Note, only full step (aka 1:1) control is supported via serial mode. No microstepping.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/16836

  Hardware Connections:

  ARDUINO --> PRODRIVER
  D8 --> STBY
  D7 --> EN
  D6 --> MODE0
  D5 --> MODE1
  D4 --> MODE2
  D3 --> MODE3
  D2 --> ERR


*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 6");

  myProDriver.settings.controlMode = PRODRIVER_MODE_SERIAL; // non-default mode must be set here
  myProDriver.begin(); // adjust custom settings before calling this
}

void loop() {
  myProDriver.setTorque(PRODRIVER_TRQ_100);
  myProDriver.stepSerial(200, 0); // turn 200 steps, CW direction
  delay(1000);
  myProDriver.setTorque(PRODRIVER_TRQ_25);
  myProDriver.stepSerial(200, 1); // turn 200 steps, CCW direction
  delay(1000);
}
