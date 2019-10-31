/*============================================================================*\
 * "Bob" Brain
 * Peter Eldred 2019-10
 * 
 * This unit contains all of Bob's thoughts, emotions and directives.
\*============================================================================*/

#include "Arduino.h"
#include "config.h"
#include "Brain.h"
#include "DriveMotors.h"

/**
 * Constructor
 */
Brain::Brain() {};


/**
 * Initialise
 */
void Brain::init() {
  // Temporary HORN code
  pinMode(PIN_HORN_ACTIVE, OUTPUT);
  pinMode(PIN_HORN_GROUND, OUTPUT);
  digitalWrite(PIN_HORN_GROUND, LOW);

  _controllerConnected = 0;
  _joystickX = 0;
  _joystickY = 0;
}


/**
 * Main Loop
 */
void Brain::update(long currentMillis) {
  driveMotors.update(currentMillis);
}


/**
 * Basically an emergency stop for when the controller is disconnected
 * and we have to stop the robot
 */
void Brain::allStop() {
  _joystickX = 0;
  _joystickY = 0;
  driveMotors.allStop();
  Serial.println("=============== ALL STOP ===============");
}


/**
 * Update the Battery Level of the controller
 */
void Brain::updateControllerBatteryLevel(byte value)
{
  Serial.print("Battery Level: ");
  Serial.println(value);
}




/**
 * Updated whether the controller is connected or not
 */
void Brain::updateControllerConnected(bool value)
{
  if (value != _controllerConnected) {
    _controllerConnected = value;
    if (!_controllerConnected) {
      Serial.println("!! Lost Connection to Controller !!");
      allStop();
    } else {
      Serial.print("Controller connected on channel ");
      Serial.println(CONTROLLER_CHANNEL);
    }
  }
}


/**
 * Update the Joystick X Position
 */
void Brain::updateJoyXInput(byte value)
{
  // TODO: at some point in the future I'm goint to have to alter dJPs Controller to figure out how to best map these values
  _joystickX = map(value, 0, 255, -253, 255);

  Serial.print("x: ");
  Serial.println(_joystickX);

  driveMotors.setInputValues(_joystickX, _joystickY);
}


/**
 * Update the Joystick Y Position
 */
void Brain::updateJoyYInput(byte value)
{
  // TODO: at some point in the future I'm goint to have to alter dJPs Controller to figure out how to best map these values
  _joystickY = map(value, 0, 255, -253, 255);

  Serial.print("y: ");
  Serial.println(_joystickY);

  driveMotors.setInputValues(_joystickX, _joystickY);
}


/**
 * Activate / Deactivate the horn
 */
void Brain::activateHorn(bool value)
{
  Serial.print("Horn: ");
  Serial.println(value);

  if (value) {
    tone(PIN_HORN_ACTIVE, 440);
  } else {
    noTone(PIN_HORN_ACTIVE);
  }
}
