/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example does a custom setup (variable resolution) 
  and turns the motor at different resolutions.
  
  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/16836

  Hardware Connections:

  ARDUINO --> PRODRIVER
  D0 --> MODE0
  D1 --> MODE1
  D2 --> MODE2
  D3 --> MODE3
  D4 --> EN
  D5 --> STBY
  D6 --> ERR

*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 3");

  //***** Configure the ProDriver's Settings *****//
  // Note, we must change settings BEFORE calling the .begin() function.
  // For this example, we will try variable 1/2 step resolution.
  // This means we can turn the motor at full step resolution or 1/2 step resolution.
  // And we can change between these two resolutions during operation.
  myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2; // 1:1 <--> 1:2

  // The following lines of code are other options you can try out.
  // Comment-out the above settings declaration, and uncomment your desired setting below.
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2; // 1:1 <--> 1:2
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4; // 1:1 <--> 1:4
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_8; // 1:1 <--> 1:8
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_16; // 1:1 <--> 1:16
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_32; // 1:1 <--> 1:32
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_64; // 1:1 <--> 1:64
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_128; // 1:1 <--> 1:128

  myProDriver.begin(); // default settings
}

void loop() {
  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_1); // change to step res 1:1
  myProDriver.step(200, 0); // turn 200 steps, CW direction
  delay(1000);
  
  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_2); // change to step res 1:2
  myProDriver.step(200, 1); // turn 200 steps, CCW direction, 
  //*Note* this will be half of the above step command because we are at 1:2 step resolution
  delay(1000);
}