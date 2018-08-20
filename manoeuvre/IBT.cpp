#include "IBT.h"

IBT::IBT(byte pin1, byte pin2) {
  _pin1 = pin1;
  _pin2 = pin2;

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
}



void IBT::stop()
{
  analogWrite(_pin1, 0);
  analogWrite(_pin2, 0);
}

void IBT::rotPos(byte pwm)
{
//  Serial.print(_pin1);
//  Serial.print(' ');
//  Serial.print(_pin2);
//  Serial.print(' ');
//  Serial.println(pwm);
  
  analogWrite(_pin1, LOW);
  analogWrite(_pin2, abs(pwm));
}

void IBT::rotNeg(byte pwm)
{
//  Serial.print(_pin1);
//  Serial.print(' ');
//  Serial.print(_pin2);
//  Serial.print(' ');
//  Serial.println(pwm);
//  
  analogWrite(_pin1, abs(pwm));
  analogWrite(_pin2, LOW);
}

