/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 24th, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example sets up the ProDriver using non-default Arduino pins, 
  and turns the motor back and forth.
  
  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/16836

  Example Non-Default Hardware Connections:

  ARDUINO --> PRODRIVER
  A0  --> STBY
  D13 --> EN
  D12 --> MODE0
  D11 --> MODE1
  D10 --> MODE2
  D9  --> MODE3
  D3  --> ERR (If using hardware interrupt, must use D2 or D3 on a Redboard)
  
*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 1");

  // Let's setup some non-default pins to use!
  // Note, to setup any non-default settings, you much do this before you call .begin()
  myProDriver.settings.standbyPin = A0;
  myProDriver.settings.enablePin = 13;
  myProDriver.settings.mode0Pin = 12;
  myProDriver.settings.mode1Pin = 11;
  myProDriver.settings.mode2Pin = 10;
  myProDriver.settings.mode3Pin = 9;
  myProDriver.settings.errorPin = 3; // (if using hardware int, choose wisely)

  myProDriver.begin(); // custom pins defined above
}

void loop() {
  myProDriver.step(200, 0); // turn 200 steps, CW direction
  delay(1000);
  myProDriver.step(200, 1); // turn 200 steps, CCW direction
  delay(1000);
}