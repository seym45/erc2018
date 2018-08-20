#include <Arduino.h>
class Sonar
{
  public:
    Sonar(byte trig, byte echo);
    int get_distance();

  private:
    byte trigPin;
    byte echoPin;
    int duration;
    int distance;
};
