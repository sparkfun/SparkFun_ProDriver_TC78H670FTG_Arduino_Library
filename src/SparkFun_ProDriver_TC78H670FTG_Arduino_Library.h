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

#ifndef _SPARKFUN_PRODRIVER_TC78H670FTG_ARDUINO_LIBRARY_H
#define _SPARKFUN_PRODRIVER_TC78H670FTG_ARDUINO_LIBRARY_H

#include <stdint.h>

// default Arduino digital pin numbers
#define PRODRIVER_DEFAULT_PIN_STBY   8
#define PRODRIVER_DEFAULT_PIN_EN     7
#define PRODRIVER_DEFAULT_PIN_MODE_0 6
#define PRODRIVER_DEFAULT_PIN_MODE_1 5
#define PRODRIVER_DEFAULT_PIN_MODE_2 4
#define PRODRIVER_DEFAULT_PIN_MODE_3 3
#define PRODRIVER_DEFAULT_PIN_ERROR  2 // chosen so INT is possible on most arduinos

// step resolution modes. 
// These are used to set the MODE PINS (0:3) during begin 
// to "bootup" the driver IC in the desired mode.
// see datasheet pg 8
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2 1
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4 2
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_8 3
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_16 4
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_32 5
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_64 6
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_128 7
#define PRODRIVER_STEP_RESOLUTION_FIXED_FULL 8
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_2 9
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_4 10
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_8 11
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_16 12
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_32 13
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_64 14
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_128 15

// step resolution options
// note, these are limited by which mode you choose.
#define PRODRIVER_STEP_RESOLUTION_1_1 1
#define PRODRIVER_STEP_RESOLUTION_1_2 2
#define PRODRIVER_STEP_RESOLUTION_1_4 4
#define PRODRIVER_STEP_RESOLUTION_1_8 8
#define PRODRIVER_STEP_RESOLUTION_1_16 16
#define PRODRIVER_STEP_RESOLUTION_1_32 32
#define PRODRIVER_STEP_RESOLUTION_1_64 64
#define PRODRIVER_STEP_RESOLUTION_1_128 128

// statuses
// used primarily to check current status
// and avoid re-writing a pin, which causes a toggle in arduino
#define PRODRIVER_STATUS_ENABLED 1
#define PRODRIVER_STATUS_DISABLED 0
#define PRODRIVER_STATUS_STANDBY_ON 1
#define PRODRIVER_STATUS_STANDBY_OFF 0

//  Setting options for commInterface
#define PRODRIVER_MODE_CLOCKIN 0 
#define PRODRIVER_MODE_SERIAL 1

//  PRODRIVERSettings
//
//  This is used by the PRODRIVER class to hold settings.  It is public within that class
//  and the user is expected to write desired values into the settings before calling
//  .begin();
struct PRODRIVERSettings
{
  public:
	
  //Main control mode and pin number variables
    uint8_t controlMode;  //Set equal to PRODRIVER_MODE_CLOCKIN or PRODRIVER_MODE_SERIAL
    uint8_t stepResolutionMode; // only used if in CLOCKIN mode, otherwise ignored
    uint8_t stepResolution; // active resolution within bounds set by stepResolutionMode
    uint8_t mode0Pin;
    uint8_t mode1Pin;
    uint8_t mode2Pin;
    uint8_t mode3Pin;
    uint8_t enablePin;
    uint8_t standbyPin;
    uint8_t errorPin;
    bool enableStatus;
    bool standbyStatus;
};

class PRODRIVER
{
public:
  //settings
  PRODRIVERSettings settings;

	//Constructor generates default PRODRIVERSettings.
  PRODRIVER( void );

  bool begin( void ); // Call to apply PRODRIVERSettings and returns ERR stat
  bool errorStat( void );
  bool step(uint16_t steps = 0, bool direction = 0, uint8_t clockDelay = 2); // returns ERR stat
  bool changeStepResolution(uint8_t resolution = PRODRIVER_STEP_RESOLUTION_1_1); // only works with "variable" step modes
  bool controlModeSelect( void );
  bool enable( void );
  bool disable( void );

private:
  bool pinSetup();
};

#endif