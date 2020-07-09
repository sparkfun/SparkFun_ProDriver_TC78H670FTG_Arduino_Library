/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example does a custom setup (variable resolution 1:1 <--> 1:8)
  and wags the motor at different resolutions.
  It changes from FULL to 1/2 to 1/4 to 1/8 and back again
  during normal stepping operations.

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
  Serial.println("SparkFun ProDriver TC78H670FTG Example 4");

  //***** Configure the ProDriver's Settings *****//
  // Note, we must change settings BEFORE calling the .begin() function.
  // For this example, we will try variable 1/8 step resolution.
  // This means we can turn the motor at full 1/2, 1/4 or 1/8 step resolution.
  // And we can change between these resolutions during operation.

  // The following lines of code are other options you can try out.
  // Comment-out/uncomment as need to select your desired setting below.
  
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2; // 1:1 <--> 1:2
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4; // 1:1 <--> 1:4
  myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_8; // 1:1 <--> 1:8
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_16; // 1:1 <--> 1:16
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_32; // 1:1 <--> 1:32
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_64; // 1:1 <--> 1:64
  // myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_128; // 1:1 <--> 1:128

  myProDriver.begin(); // default settings
}

void loop() {
  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_1); // change to step res 1:1
  wagMotor();

  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_2); // change to step res 1:2
  wagMotor();

  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_4); // change to step res 1:4
  wagMotor();

  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_8); // change to step res 1:8
  wagMotor();

  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_4); // change to step res 1:4
  wagMotor();

  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_2); // change to step res 1:2
  wagMotor();
}

void wagMotor( void )
{
  myProDriver.step(200, 0); // turn 200 steps, CCW direction,
  myProDriver.step(200, 1); // turn 200 steps, CCW direction
}
