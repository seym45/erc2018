
#include "L298.h"


#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

L298::L298(byte enable, byte pin1, byte pin2) {
  _currentPwm = 0;
  _minimumSpeed = 0;
  _enable = enable;
  _pin1 = pin1;
  _pin2 = pin2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}  

void L298::stop()
{
  _currentPwm = 0;
  analogWrite(_enable, 0);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void L298::rotPos(byte pwm)
{
  _currentPwm = pwm;
  analogWrite(_enable, pwm);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, HIGH);
}

void L298::rotNeg(byte pwm)
{
  _currentPwm = pwm;
  analogWrite(_enable, pwm);
  digitalWrite(_pin1, HIGH);
  digitalWrite(_pin2, LOW);
}

// AF Motor compatible functions
void L298::run(uint8_t cmd) {
  switch (cmd) {
    case FORWARD:
      analogWrite(_enable, _currentPwm);
        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
    break;
    case BACKWARD:
    analogWrite(_enable, _currentPwm);
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, HIGH);
    break;
    case RELEASE:
      // Free running motor Stop = Slow Motor Stop is done when Enable = LOW and NOT PWM
    // and pin1/pin2 = Dont Care 
      _currentPwm = 0;
    digitalWrite(_enable,LOW);
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    break;
    case BRAKE: 
      // Fast motor Stop = Brake is done when Enable = HIGH and NOT PWM
    // and pin1 is equal pin2.
    // pin1 = Pin2 = LOW. Equal with RELEASE. Differance is that Enable is HIGH
      _currentPwm = 0;
    digitalWrite(_enable,HIGH);
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    break;
  }
}

// 
void L298::setSpeed(uint8_t speed) {
    // Map the speed to motors working PWM to aviod individual motors unusable PWM range from 0 to "lowestPWM where the motor starts"
    if (speed == 0)
      _currentPwm = 0;
    else  
      _currentPwm = map(speed,0,255,_minimumSpeed,255);
  analogWrite(_enable, _currentPwm);
}
// set speed in percentage from -100 to 100
void L298::setSpeedPercentage(float speed) {
  // anothing above 100 or below -100 is invalid
  if (speed > 100)
    speed = 100;
  else if (speed < -100)
    speed = -100;
  
  // negative speed 
  if (speed > 0) {
    run(FORWARD);
    setSpeed((uint8_t) (255/100 * speed));
  }
  else if (speed < 0){
    run(BACKWARD);
    setSpeed((uint8_t) (-255/100 * speed));
  }
  else {
    setSpeed((uint8_t) 0);
  }
}

uint8_t L298::getSpeed(void) {
    // Simply return the privat _currentPwm that holds the latest setSpeed.
  return _currentPwm;
}

void L298::setMinimumSpeed(uint8_t minimumSpeed) {
    // Set individual motors unusable PWM range from 0 to "lowestPWM where the motor starts"
  _minimumSpeed = minimumSpeed; 
}
