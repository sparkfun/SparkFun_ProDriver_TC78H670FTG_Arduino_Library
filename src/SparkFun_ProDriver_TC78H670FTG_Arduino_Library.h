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

#ifndef _SPARKFUN_QWIIC_DUAL_ENCODER_READER_ARDUINO_LIBRARY_H
#define _SPARKFUN_QWIIC_DUAL_ENCODER_READER_ARDUINO_LIBRARY_H
#include "Arduino.h"

#define PRODRIVER_MODE_CLOCKIN 0 
#define PRODRIVER_MODE_SERIAL 1

#define PRODRIVER_DEFAULT_PIN_MODE_0 0
#define PRODRIVER_DEFAULT_PIN_MODE_1 1
#define PRODRIVER_DEFAULT_PIN_MODE_2 2
#define PRODRIVER_DEFAULT_PIN_MODE_3 3
#define PRODRIVER_DEFAULT_PIN_EN     4
#define PRODRIVER_DEFAULT_PIN_STBY   5

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

class PRODRIVER
{
public:
  PRODRIVER();

  boolean begin(boolean mode = PRODRIVER_MODE_CLOCKIN, 
                uint8_t stepResolution = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2,
                uint8_t standByPin = PRODRIVER_DEFAULT_PIN_STBY, 
                uint8_t enablePin = PRODRIVER_DEFAULT_PIN_EN, 
                uint8_t modePin0 = PRODRIVER_DEFAULT_PIN_MODE_0, 
                uint8_t modePin1 = PRODRIVER_DEFAULT_PIN_MODE_1, 
                uint8_t modePin2 = PRODRIVER_DEFAULT_PIN_MODE_2, 
                uint8_t modePin3 = PRODRIVER_DEFAULT_PIN_MODE_3
                );

  boolean isError();
  
private:

};

#endif