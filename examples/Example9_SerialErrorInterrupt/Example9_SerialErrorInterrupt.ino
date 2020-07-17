/*
  Control a bi-polar stepper motor using the SparkFun ProDriver TC78H670FTG
  By: Pete Lewis
  SparkFun Electronics
  Date: July 2nd, 2020
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example turns the motor back in Serial Mode, and with an interrupt to watch the ERR pin.
  If an error is detected by the IC, this program will stop and print,
  "Error Detected!!", and with for user serial input to begin again.

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
  D2 --> ERR   ***DEFAULT ERROR INTERRUPT PIN***


*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object

void setup() {
  Serial.begin(115200);
  Serial.println("SparkFun ProDriver TC78H670FTG Example 9");

  myProDriver.settings.controlMode = PRODRIVER_MODE_SERIAL; // non-default mode must be set here
  myProDriver.settings.openDetection = PRODRIVER_OPD_OFF;

  myProDriver.begin(); // adjust custom settings before calling this

  myProDriver.enable(); // must enable here (before calling a stepSerial)
  // because the enable/err net is default tied low on the ProDriver.
  // if we don't enable, then this will fire the error int, and give us a false error on bootup

  attachInterrupt(digitalPinToInterrupt(myProDriver.settings.errorPin), error, FALLING); // default error pin (D2), active low
  // note, it's important to attach interrupt after setup and enable, because that is default low on ProDriver harware.
}

void loop() {
  if (myProDriver.settings.errorFlag == false)
  {
    Serial.println("Stepping 200 steps CW");
    myProDriver.stepSerial(200, 0); // turn 200 steps, CW direction
    errorCheckDelay(1000);

    if (myProDriver.settings.errorFlag == false) // only attempt the CCW motion if there was no error
    { Serial.println("Stepping 200 steps CCW");
      myProDriver.stepSerial(200, 1); // turn 200 steps, CCW direction
      errorCheckDelay(1000);
    }
  }
  else {
    Serial.println("Error detected!!");
    myProDriver.disable(); // disable motor driver
    digitalWrite(myProDriver.settings.standbyPin, LOW);
    myProDriver.settings.standbyStatus = PRODRIVER_STATUS_STANDBY_ON;
    delay(3000);

    Serial.println("Type any character to begin testing again");
    while (Serial.available() < 1); // do nothing until user types something into the serial monitor
    serialFlush(); // clear out everything

    Serial.println("Booting up ProDriver again...");
    myProDriver.begin();
    delayMicroseconds(200);
    myProDriver.enable();
    delayMicroseconds(200);
    myProDriver.settings.errorFlag = false; // reset errorFlag
  }
}

void error( void ) {
  myProDriver.settings.errorFlag = true;
}

void errorCheckDelay(int delayTime)
{
  // delay for some amount of ms, but continue to check for errorFlag
  for (int i = 0 ; i < delayTime ; i++)
  {
    if (myProDriver.settings.errorFlag == false) delay(1);
    else break;
  }
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
