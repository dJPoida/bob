#ifndef config_h
#define config_h

#include "Arduino.h"

// Current Firmware Version
#define VERSION 1.0

// Temporary Pins for the horn
#define PIN_HORN_ACTIVE A3
#define PIN_HORN_GROUND A0

// DJPs Controller (Radio Configuration)
#define PIN_CE 9
#define PIN_CSN 10
#define CONTROLLER_CHANNEL 1

// Adafruit Motor Controller
// Select which 'port' M1, M2, M3 or M4
#define MOTOR_FR 3
#define MOTOR_FL 4
#define MOTOR_BR 2
#define MOTOR_BL 1

// Indicate Whether the motors require their directions to be inverted
#define MOTOR_FR_INVERT_DIR 0
#define MOTOR_FL_INVERT_DIR 1
#define MOTOR_BR_INVERT_DIR 1
#define MOTOR_BL_INVERT_DIR 0

// Other Motor Parameters
#define MOTOR_SHIELD_I2C_ADDRESS 0x60 // Default is 0x60
#define MOTOR_SHIELD_FREQ 1600 // Default is 1.6khz
#define MOTOR_MAX_SPEED 255 // 0 - 255

// How often should the motors re-calculate their target velocities
#define MOTOR_UPDATE_INTERVAL 5 // ms
#define MOTOR_ACCELLERATION_RATE 5 // % / update

#endif
