
#ifndef L298_H
#define L298_H


#include <Arduino.h>


// AF motor Compatible defines
// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3      // Function defined in AF_Motor but not implemented
#define RELEASE 4                                                                                          


class L298
{
  public:
    L298(byte enable, byte pin1, byte pin2);
  void stop();
  void rotPos(byte pwm);
    void rotNeg(byte pwm);
  
  // AF Motor Compatible functions
  void run(uint8_t);
    void setSpeed(uint8_t);
  void setSpeedPercentage(float);
  
  // Not implemented in AF_Motor, but adds functionality to AF_Motor functions
  uint8_t getSpeed(void);
  void setMinimumSpeed(uint8_t);
  
  private:
    byte _currentPwm;
  byte _minimumSpeed;
    byte _enable;
  byte _pin1;
  byte _pin2;
};

#endif
