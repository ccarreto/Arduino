#include "SimpleMotor.h"

SimpleMotor leftMotor(6, 7, 150);
SimpleMotor rightMotor(5, 4, 150);

int leftPower;
int rightPower;
int time;

void setup() {
  randomSeed(analogRead(0));
}

void loop() {
   
  leftPower = random(-16, 17);
  rightPower = random(-16, 17);
  //time = random(100, 401);
  time = random(401) + 100;
  move(leftPower, rightPower, time);
}

void move(int leftPower, int rightPower, int time) 
{
  leftMotor.setPower(leftPower);
  rightMotor.setPower(rightPower);
  delay(time);
}
