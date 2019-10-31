/*============================================================================*\
 * "Bob" Robot Main Control systems
 * dJPoida (aka Peter Eldred) 2019-10
\*============================================================================*/


/** 
 * Includes
 */
#include <Wire.h>
#include <DJPsReceiver.h>
#include <Adafruit_MotorShield.h>
#include "config.h"
#include "Brain.h"
#include "DriveMotors.h"


/**
 * Global Varibles
 */
DJPsReceiver receiver(PIN_CE, PIN_CSN, CONTROLLER_CHANNEL);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(MOTOR_SHIELD_I2C_ADDRESS);
Brain brain = Brain();
DriveMotors driveMotors = DriveMotors();


/**
 * Main Setup
 */
void setup() {
  Serial.begin(115200);
  Serial.print("Bob Firmware v");
  Serial.println(VERSION);
  Serial.println("Initialising...");

  // Setup the Drive Motors
  Serial.println(" - Drive Motors");
  driveMotors.init(&AFMS);

  // Setup the Brain
  Serial.println(" - Brain");
  brain.init();

  // Start listening to dJPs Receiver
  Serial.println(" - Receiver");
  setupReceiver();

  Serial.println("Initialised.");
  Serial.println("Rock and Roll.");
  Serial.println("");
}


/**
 * Main Loop
 */
void loop() {
  long currentMillis = millis();
  
  // Think baby!
  brain.update(currentMillis);

  // Check to see if the receiver has noticed any changes in the controller
  receiver.run();
}
