/*============================================================================*\
 * "Bob" Brain
 * Peter Eldred 2019-10
 * 
 * This unit controls Bob's drive system
\*============================================================================*/

#ifndef DriveMotors_h
#define DriveMotors_h

#include <Adafruit_MotorShield.h>

class DriveMotors{
  public:
    DriveMotors();
    void init(Adafruit_MotorShield *AFMS);
    void update(long currentMillis);

    void setInputValues(int inputX, int inputY);

    void allStop();

  private:
    Adafruit_MotorShield *_AFMS;
    Adafruit_DCMotor *motorFR;
    Adafruit_DCMotor *motorFL;
    Adafruit_DCMotor *motorBR;
    Adafruit_DCMotor *motorBL;

    long lastUpdateTime = 0;
    
    int _inputX; // -255 -> 255
    int _inputY; // -255 -> 255

    int _leftSpeed; // -255 -> 255
    int _rightSpeed; // -255 -> 255

    int _targetLeftSpeed; // -255 -> 255
    int _targetRightSpeed; // -255 -> 255

    bool _leftDirection; // 0 = reverse, 1 = forwards
    bool _rightDirection; // 0 = reverse, 1 = forwards

    void _updateTargets();
    void _updateSpeeds();
    
    void _setMotorDirectionAndSpeed(Adafruit_DCMotor *motor, int speed, bool direction, bool invertDirection);
};

extern DriveMotors driveMotors;

#endif
