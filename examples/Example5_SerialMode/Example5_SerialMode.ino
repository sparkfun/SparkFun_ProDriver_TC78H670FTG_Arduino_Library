/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example does a custom setup (controlMode:SERIAL) and turns the motor back and forth.

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
  Serial.println("SparkFun ProDriver TC78H670FTG Example 5");

  myProDriver.settings.controlMode = PRODRIVER_MODE_SERIAL;
  myProDriver.begin(); // adjust custom settings before calling this
}

void loop() {
  stepSerial(50); // turn 200 steps
  delay(1000);
  stepSerialCCW(50); // turn 200 steps
  delay(1000);
}

void stepSerial( uint8_t steps)
{
  myProDriver.enable(); // in serial mode, we must call enable here, 
  // before we start commanding current/phase of each coil

  for (uint16_t i = 0 ; i < steps ; i++)
  {
    myProDriver.settings.phaseA = 1;
    myProDriver.settings.phaseB = 1;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 0;
    myProDriver.settings.phaseB = 1;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 0;
    myProDriver.settings.phaseB = 0;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 1;
    myProDriver.settings.phaseB = 0;
    myProDriver.sendSerialCommand();
    delay(2);
  }
}

void stepSerialCCW( uint8_t steps)
{
  myProDriver.enable(); // in serial mode, we must call enable here, 
  // before we start commanding current/phase of each coil

  for (uint16_t i = 0 ; i < steps ; i++)
  {
    myProDriver.settings.phaseA = 1;
    myProDriver.settings.phaseB = 1;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 1;
    myProDriver.settings.phaseB = 0;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 0;
    myProDriver.settings.phaseB = 0;
    myProDriver.sendSerialCommand();
    delay(2);

    myProDriver.settings.phaseA = 0;
    myProDriver.settings.phaseB = 1;
    myProDriver.sendSerialCommand();
    delay(2);
  }
}
