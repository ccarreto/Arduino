/*
  SimpleMotor.cpp - Library for control of a motor.

  Assumes a motor driver that uses 2 pins:
  - Power pin (powerPin) -> PWM (0-255)
  - Direction pin (dirPin) -> High or Low

  Uses a power scale of (0 .. 16) that is maped into the scale (minPower .. 255)

  Created by C. Carreto, last revision May 15, 2015.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include "Arduino.h"
#include "SimpleMotor.h"

SimpleMotor::SimpleMotor(int _powerPin, int _dirPin, int _minPower)
{
  powerPin = _powerPin;
  pinMode(powerPin, OUTPUT);
  
  dirPin = _dirPin;
  pinMode(dirPin, OUTPUT);
  
  minPower = _minPower;
}

void SimpleMotor::setPower(int power)
{
  if(power == 0) {
    stop();
    return;
  }
  
  if(power < 0) {
    power = -power;
    digitalWrite(dirPin, HIGH);
  }
  else {
    digitalWrite(dirPin, LOW);
  }  
  analogWrite(powerPin, convert(power));
}

void SimpleMotor::stop()
{
   analogWrite(powerPin, 0);
}

int SimpleMotor::convert(int v)
{
  if(v > 16) v = 16; 
  return map(v, 0, 16, minPower, 255);
}
