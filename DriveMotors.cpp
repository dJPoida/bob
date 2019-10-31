/*============================================================================*\
 * "Bob" Brain
 * Peter Eldred 2019-10
 * 
 * This unit controls Bob's drive system
\*============================================================================*/

#include "config.h"
#include "DriveMotors.h"

#include <Adafruit_MotorShield.h>

/**
 * Constructor
 */
DriveMotors::DriveMotors(){
  _targetLeftSpeed = 0;
  _targetRightSpeed = 0;

  _leftSpeed = 0;
  _rightSpeed = 0;

  _leftDirection = 1;
  _rightDirection = 1;
}


/**
 * Initialise
 */
void DriveMotors::init(Adafruit_MotorShield *AFMS){
  // Keep a pointer to the Adafruit Motor Shield
  _AFMS = AFMS;

  // Attach our Motors to the Adafruit Motor Shield
  motorFR = _AFMS->getMotor(MOTOR_FR);
  motorFL = _AFMS->getMotor(MOTOR_FL);
  motorBR = _AFMS->getMotor(MOTOR_BR);
  motorBL = _AFMS->getMotor(MOTOR_BL);

  _AFMS->begin(MOTOR_SHIELD_FREQ);
}  


/**
 * Main Loop
 */
void DriveMotors::update(long currentMillis) {
  if (lastUpdateTime + MOTOR_UPDATE_INTERVAL < currentMillis) {
    _updateTargets();
    _updateSpeeds();
  }
}


/**
 * All Stop is basically an emergency for when we don't want
 * to stack the bot into the wall after the controller disconnects
 */
void DriveMotors::allStop() {
  _inputX = 0;
  _inputY = 0;
  _targetLeftSpeed = 0;
  _targetRightSpeed = 0;
  _updateSpeeds();
}


/**
 * Called by the brain in response to an input from the controller
 */
void DriveMotors::setInputValues(int inputX, int inputY) {
  _inputX = inputX;
  _inputY = inputY;
  
  Serial.print("Drive: ");
  Serial.print(_inputX);
  Serial.print(",");
  Serial.println(_inputY);
}


/**
 * Evaluate the input and transform the X and Y values into Left and Right target speeds
 */
void DriveMotors::_updateTargets() {
  // http://home.kendra.com/mauser/joystick.html
  int x = map(_inputX, -255, 255, -100, 100) * -1;
  int y = map(_inputY, -255, 255, -100, 100);
  
  float v = (100 - abs(x)) * (y / 100) + y;
  float w = (100 - abs(y)) * (x / 100) + x;
  
  _targetRightSpeed = map((v + w) / 2, -100, 100, -255, 255);
  _targetLeftSpeed = map((v - w) / 2, -100, 100, -255, 255);
}


/**
 * Called by the update() method to bring the current speeds of the motors toward the target speeds
 */
void DriveMotors::_updateSpeeds() {
  // Left motors
  if (_targetLeftSpeed != _leftSpeed) {
    // Graduate the left speed based on the accelleration rate
    if (_targetLeftSpeed > _leftSpeed) {
      _leftSpeed += MOTOR_ACCELLERATION_RATE;
    } else {
      _leftSpeed -= MOTOR_ACCELLERATION_RATE;
    }
    _leftSpeed = constrain(_leftSpeed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);

    // Set the drive direction of the left motors
    _setMotorDirectionAndSpeed(motorFL, abs(_leftSpeed), (_leftSpeed >= 0), MOTOR_FL_INVERT_DIR);
    _setMotorDirectionAndSpeed(motorBL, abs(_leftSpeed), (_leftSpeed >= 0), MOTOR_BL_INVERT_DIR);
  }

  // Right motors
  if (_targetRightSpeed != _rightSpeed) {
    // Graduate the right speed based on the accelleration rate
    if (_targetRightSpeed > _rightSpeed) {
      _rightSpeed += MOTOR_ACCELLERATION_RATE;
    } else {
      _rightSpeed -= MOTOR_ACCELLERATION_RATE;
    }
    _rightSpeed = constrain(_rightSpeed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);

    // Set the drive direction of the left motors
    _setMotorDirectionAndSpeed(motorFR, abs(_rightSpeed), (_rightSpeed >= 0), MOTOR_FR_INVERT_DIR);
    _setMotorDirectionAndSpeed(motorBR, abs(_rightSpeed), (_rightSpeed >= 0), MOTOR_BR_INVERT_DIR);
  }
}


/**
 * Sets the direction and speed of one of the motors on the robot
 */
void DriveMotors::_setMotorDirectionAndSpeed(Adafruit_DCMotor *motor, int speed, bool direction, bool invertDirection) {
  motor->setSpeed(speed);
  if (invertDirection) {
    motor->run(direction ? BACKWARD : FORWARD);
  } else {
    motor->run(direction ? FORWARD : BACKWARD);
  }
}
