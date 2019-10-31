/**
 * Fired when the Battery Level on the Controller Changes
 */
void handleBatteryLevelChanged(byte value) {
  brain.updateControllerBatteryLevel(value);
}


/**
 * Fired when the state of Button A on the controller changes between 0 / 1
 */
void handleBtnAChanged(bool value) {
  // Activate the horn
  brain.activateHorn(value);
}


/**
 * Fired when the state of the Joystick X Axis changes (0-255)
 */
void handleJoyXChanged(byte value) {
  Serial.println(value);
  brain.updateJoyXInput(value);
}


/**
 * Fired when the state of the Joystick Y Axis changes (0-255)
 */
void handleJoyYChanged(byte value) {
  brain.updateJoyYInput(value);
}


/**
 * Fired when the receiver is connected to the controller
 */
void handleConnected() {
  brain.updateControllerConnected(1);
}


/**
 * Fired when the receiver is disconnected from the controller
 */
void handleDisconnected() {
  brain.updateControllerConnected(0);
}


/**
 * Called during the initialisation of the code to setup the handlers
 */
void setupReceiver() {
  receiver.onBatteryLevelChange = handleBatteryLevelChanged;
  receiver.onBtnAChange = handleBtnAChanged;
  receiver.onJoyXChange = handleJoyXChanged;
  receiver.onJoyYChange = handleJoyYChanged;
  receiver.onConnected = handleConnected;
  receiver.onDisconnected = handleDisconnected;
  receiver.begin();
}
