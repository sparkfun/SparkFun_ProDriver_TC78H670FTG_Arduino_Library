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

//Constructor
PRODRIVER::PRODRIVER()
{
}

//Initializes the motor driver with basic settings
//Returns false if error is detected (i.e. ERR pin is pulled low by the IC)
boolean PRODRIVER::begin(boolean mode, uint8_t stepResolution, uint8_t standByPin, uint8_t enablePin, uint8_t modePin0, uint8_t modePin1, uint8_t modePin2, uint8_t modePin3)
{

  if (isError() == false)
    return (false); //Check for sensor presence

  return (true); //We're all setup!
}
