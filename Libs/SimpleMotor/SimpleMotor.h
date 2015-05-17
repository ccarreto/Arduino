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

#ifndef SimpleMotor_h
#define SimpleMotor_h

class SimpleMotor
{
  public:
    SimpleMotor(int _powerPin, int _dirPin, int _minPower);
    void setPower(int power);
    void stop();
    int convert(int v);
     
   private:
    int powerPin;
    int dirPin;  
    int minPower; 
};

#endif
