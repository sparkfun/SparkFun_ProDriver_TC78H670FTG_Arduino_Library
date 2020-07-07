/*
  This is a library written for the SparkFun ProDriver TC78H670FTG Stepper Motor Driver
  
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/16836

  Written by Pete Lewis @ SparkFun Electronics, July 6th, 2020

  The SparkFun ProDriver is a stepper motor driver that can be controlled via "clock in mode" or "serial mode".
  This library provides control of the following features:
    -setup (includes mode and resolution select)
    -movement commands via clock-in mode and serial mode
    -max current control (as a percentage of VREF - which is set with a trimpot on the product)
    -change step resolution (using SET_EN, UP-DOWN and CLK)

  https://github.com/sparkfun/SparkFun_ProDriver_TC78H670FTG_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h"
#include "Arduino.h"

//****************************************************************************//
//
//  Constructor
//
//    Initalizes settings to default.
//
//****************************************************************************//
PRODRIVER::PRODRIVER( void )
{
	//Construct with these default settings if nothing is specified

	//Select control mode
	settings.controlMode = PRODRIVER_MODE_CLOCKIN; // PRODRIVER_MODE_CLOCKIN or PRODRIVER_MODE_SERIAL
	settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_FIXED_FULL; // many options, see header file or ds pg 8
  
  //Select default arduino pin numbers for hardware connections
	settings.mode0Pin =   PRODRIVER_DEFAULT_PIN_MODE_0;
  settings.mode1Pin =   PRODRIVER_DEFAULT_PIN_MODE_1;
  settings.mode2Pin =   PRODRIVER_DEFAULT_PIN_MODE_2;
  settings.mode3Pin =   PRODRIVER_DEFAULT_PIN_MODE_3;
  settings.enablePin =  PRODRIVER_DEFAULT_PIN_EN;
  settings.standbyPin = PRODRIVER_DEFAULT_PIN_STBY;
  settings.errorPin =   PRODRIVER_DEFAULT_PIN_ERROR;
}

//Initializes the motor driver with basic settings
//Returns false if error is detected (i.e. ERR pin is pulled low by the IC)
boolean PRODRIVER::begin( void )
{
  pinSetup(); // sets arduino pins to necessary initial pinModes and statuses
  controlModeSelect(); // "boots up" IC with correct statuses on MODE pins

  return errorStat(); //We're all setup!
}

// pinSetup( void )
// setup Arduino pins as inputs/outputs as needed, and to default settings (disabled, standby)
boolean PRODRIVER::pinSetup( void )
{
  // standby is active low. 
  // OUTPUT, LOW = standby
  // OUTPUT, HIGH = not in standby
  pinMode(settings.standbyPin, OUTPUT);
  digitalWrite(settings.standbyPin, LOW); // hold in standby, until we're ready to go

  // enable is active high 
  // OUTPUT, HIGH = enabled (Must also have hardware switch set to "USER")
  // INPUT, LOW = disabled (on-board pulldown will disable)
  // note, hardware slide switch can also over-ride this when set to "OFF"
  pinMode(settings.enablePin, INPUT);
  digitalWrite(settings.enablePin, LOW); // disabled, input without pullup 

  // error is active low 
  // This will always be an input pin (on your microcontroller)
  // note, this pin on the IC has a dual purpose (both EN and ERR).
  pinMode(settings.errorPin, INPUT); // input without pullup 

  // all mode pins to output low
  pinMode(settings.mode0Pin, OUTPUT);
  digitalWrite(settings.mode0Pin, LOW);
  pinMode(settings.mode1Pin, OUTPUT);
  digitalWrite(settings.mode1Pin, LOW);
  pinMode(settings.mode2Pin, OUTPUT);
  digitalWrite(settings.mode2Pin, LOW);
  pinMode(settings.mode3Pin, OUTPUT);
  digitalWrite(settings.mode3Pin, LOW);      

}

// controlModeSelect( void )
// This "boots up" the IC into the desired mode.
// VM (the main motor voltage supply) must be stable
// Must be in standby mode.
// Mode pins must be set to desired mode, then standby must be released.
// see datasheet pg 6
boolean PRODRIVER::controlModeSelect( void )
{
  // set mode pins according to desired mode
  switch (settings.controlMode)
  {
  case PRODRIVER_MODE_SERIAL:
    // set mode pins to all LOW for serial mode
    digitalWrite(settings.mode0Pin, LOW);
    digitalWrite(settings.mode1Pin, LOW);
    digitalWrite(settings.mode2Pin, LOW);
    digitalWrite(settings.mode3Pin, LOW);     
    break;

  case PRODRIVER_MODE_CLOCKIN:
    // set mode pins as needed
    // note, when you set controlmode to CLOCKIN,
    // you are also setting the step resolution, which can
    // be a variety of options.

    // grab "bits" from the desired step resolution
    // these will be used to set each mode pin high/low

    digitalWrite(settings.mode0Pin, bitRead(settings.stepResolutionMode, 0));
    digitalWrite(settings.mode1Pin, bitRead(settings.stepResolutionMode, 1));
    digitalWrite(settings.mode2Pin, bitRead(settings.stepResolutionMode, 2));
    digitalWrite(settings.mode3Pin, bitRead(settings.stepResolutionMode, 3));
    break;

  default:
    break;

  }
  
  // wait TmodeSU (mode setting setup time) minimum 1 microsecond
  delayMicroseconds(1);

  // release standby (write it HIGH)
  digitalWrite(settings.standbyPin, HIGH);

  // wait TmodeHO (mode setting Data hold time) minimum 100 microseconds
  delayMicroseconds(100);

  // engage standby (write it LOW)
  digitalWrite(settings.standbyPin, LOW);
  return errorStat();
}

// errorStat( void )
// checks the status of the ERR net.
// Note, one pin on the IC shares the purpose of both ERR and EN (enable)
// If ERR reads low, then one of three things is wrong:
// Thermal shutdown (TSD) 
// Overcurrent (ISD)
// Motor Load Open (OPD)
// returns true if things are good and there is no error detected

boolean PRODRIVER::errorStat( void )
{
  if(digitalRead(settings.errorPin) == true)
  {
    return true; // there is no error, so let's indicate that with a true.
  }
  return false; // if we get here, then errorPin was low, indicating an error
  // false means error!
}

// step( uint16_t steps, boolean direction )
// step the motor a set amount of steps at the desired direction
// will stop if error is detected during stepping
// retuns errorStat()

boolean PRODRIVER::step( uint16_t steps, boolean direction)
{
  // set CW-CWW pin (aka mode3pin) to the desired direction
  // CW-CCW pin controls the rotation direction of the motor. 
  // When set to H, the current of OUT_A is output first, with a phase difference of 90°. 
  // When set to L, the current of OUT_B is output first with a phase difference of 90°
  digitalWrite(settings.mode3pin, direction);
  
  // step the motor the desired amount of steps
  // each up-edge of the CLK signal (aka mode2pin) 
  // will shift the motor's electrical angle per step.
  for(uint16_t i = 0 ; i < steps ; i++)
  {
    digitalWrite(settings.mode2Pin, LOW);
    digitalWrite(settings.mode2Pin, HIGH);
    // check for error
    if(errorStat() == false) return false; // error detected, exit out of here!
  }
  return errorStat();
}

// changeStepResolution( uint8_t resolution)
// Step resolution can be changed during operating.
// Step resolution can be set by SET_EN pin and UP-DW pin. 
// Step mode is changed synchronously with Step Clock. 
// see datasheet pg 9
boolean PRODRIVER::changeStepResolution( uint8_t resolution)
{
  // If user asks to change resolution, but we are already there, then
  // just return errorStat()
  if(settings.stepResolution == resolution) return errorStat();


  // convert pin names to CLOCKIN specific names
  // (for ease of programming)
  uint8_t setEn = settings.mode1pin
  uint8_t updw = settings.mode0pin
  uint8_t clock = settings.mode2pin

  // setup pins for a new step resolution change
    digitalWrite(clock, HIGH);
    digitalWrite(setEn, HIGH);

  // find out how many shifts we need in either direction.
  uint8_t shifts = 0;

  // resolution and settings.stepResolution actually are the divisor of the step resolution fraction,
  // so we can compare the two to find out whether we need to "upshift" or "downshift"
  // if the new desired setting (resolution) is a larger number, then that means we are actually
  // moving from a lower resolution to a higher one (like moving from 1:1 to 1:8)
  if(resolution > settings.stepResolution) // we are moving to a higher resolution
  {
    if ( (resolution / 2) == settings.stepResolution ) shift = 1;
    else if ( (resolution / 4) == settings.stepResolution ) shift = 2;
    else if ( (resolution / 8) == settings.stepResolution ) shift = 3;
    else if ( (resolution / 16) == settings.stepResolution ) shift = 4;
    else if ( (resolution / 32) == settings.stepResolution ) shift = 5;
    else if ( (resolution / 64) == settings.stepResolution ) shift = 6;
    else if ( (resolution / 128) == settings.stepResolution ) shift = 7;
    digitalWrite(updw, LOW);
  }
  else{ // we are moding to lower resolution
    if ( (settings.resolution / 2) == resolution ) shift = 1;
    else if ( (settings.resolution / 4) == resolution ) shift = 2;
    else if ( (settings.resolution / 8) == resolution ) shift = 3;
    else if ( (settings.resolution / 16) == resolution ) shift = 4;
    else if ( (settings.resolution / 32) == resolution ) shift = 5;
    else if ( (settings.resolution / 64) == resolution ) shift = 6;
    else if ( (settings.resolution / 128) == resolution ) shift = 7;
    digitalWrite(updw, HIGH);
  }

  // toggle clock cycles as needed to cause the right amount of "shifts" in resolution
  for(uint8_t i = 0 ; i < shift ; i++)
  {
    digitalWrite(clock, LOW);
    digitalWrite(clock, HIGH);
  }

  // we're finished, so let's set SET_EN back to LOW, so it doesn't look at UP-DW anymore
  digitalWrite(setEn, LOW);
  
  return errorStat();
}