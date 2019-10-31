/*============================================================================*\
 * "Bob" Brain
 * Peter Eldred 2019-10
 * 
 * This unit contains all of Bob's thoughts, emotions and directives.
\*============================================================================*/

#ifndef Brain_h
#define Brain_h

#include "Arduino.h"

class Brain
{
  public:
    Brain();
    void init();
    void update(long currentMillis);

    void updateControllerBatteryLevel(byte value);
    void updateControllerConnected(bool value);
    void updateJoyXInput(byte value);
    void updateJoyYInput(byte value);
    void activateHorn(bool);
  
    void allStop();

  private:
    int _joystickX; // -255 -> 255
    int _joystickY; // -255 -> 255 
    bool _controllerConnected;
};

extern Brain brain;

#endif
