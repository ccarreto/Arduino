/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef RMotor_h
#define RMotor_h

#include "Arduino.h"

class RMotor
{
  public:
    RMotor(int powerPin, int dirPin, int minPower);
    void setPower(int power);
    void stop();
    int convert(int v);
  private:
    int _minPower;
    int _powerPin;
    int _dirPin;
};

#endif
