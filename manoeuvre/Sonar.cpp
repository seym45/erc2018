#include "Sonar.h"

Sonar::Sonar(byte trig, byte echo)
{
  trigPin = trig;
  echoPin = echo;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int Sonar::get_distance()
{
  digitalWrite(trigPin, LOW); // Added this line
  delayMicroseconds(2);       // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH,4000);
  distance = (duration / 2) / 29.1;
  
  return duration;
}
