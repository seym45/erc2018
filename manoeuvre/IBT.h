#include <Arduino.h>

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

class IBT
{
  public:
    IBT(byte pin1, byte pin2);
    void stop();
    void rotPos(byte pwm);
    void rotNeg( byte pwm);

  private:
    byte _pin1;
    byte _pin2;
};

