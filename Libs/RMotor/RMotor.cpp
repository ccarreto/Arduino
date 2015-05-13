/*
  RMotor.cpp - Library for control of a motor.

  Assums a motor driver that uses 2 pins:
  - Power pin (powerPin) -> PWM (0-255)
  - Direction pin (dirPin) -> High or Low

  Uses a power scale of (0 .. 16) that is maped into the scale (minPower .. 255)

  Created by C. Carreto, April 27, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "RMotor.h"

RMotor::RMotor(int powerPin, int dirPin, int minPower)
{
  pinMode(powerPin, OUTPUT);
  _powerPin = powerPin;
  pinMode(dirPin, OUTPUT);
  _dirPin = dirPin;
  if (minPower < 0) minPower = 0;
  else if (minPower > 255) minPower = 255;
  _minPower = minPower;
}

void RMotor::setPower(int power)
{
  if (power < 0) {
    power = - power;
    analogWrite(_powerPin, convert(power));
    digitalWrite(_dirPin, HIGH);
  }
  else {
    analogWrite(_powerPin, convert(power));
    digitalWrite(_dirPin, LOW);
  }
}

void RMotor::stop()
{
    analogWrite(_powerPin, 0);
}

int RMotor::convert(int v)
{
  if (v < 0)
    v = 0;
  else if (v > 16)
    v = 16;
  return map(v, 0, 16, _minPower, 255);
}
