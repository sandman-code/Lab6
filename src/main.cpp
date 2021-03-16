#include <Bluemotor.h>
#include <Arduino.h>
#include <Romi32U4.h>
#include "PID.h"

Romi32U4ButtonB pb;

Romi32U4Motors motors;

PID controlPID(400.0, 0.0, 0.05, 5.0, 3.0);

Bluemotor motor;
long oldReading = 0;
long newReading = 0;
long old = 0;
float newt = 0;
long freq = 0;

void setup()
{
  Serial.begin(9600);
  motor.initilize(); // put your setup code here, to run once:
}

void loop()
{
  //Part 1
  for (int i = 0; i < 400; i++)
  {
    motor.setEffort(i);
    Serial.println(i);
  }

  //Part 2
  if (millis() % 10 == 0)
  {
    motor.setEffortWithoutDB((int)controlPID.calculate(1000.0, motor.getPosition()));
  }
  /*
  if (pb.isPressed())
  {
    newt = millis() / 1000;
    newReading = motor.getPosition();
    freq = (newReading - oldReading) / (newt - old);
    unsigned long endTime = millis() + 100;
    motor.setEffort(200); // effort test value
    Serial.println(motor.getPosition());
    Serial.println(millis());
    Serial.println((freq * 60) / 540);
    Serial.println();
    while (millis() < endTime)
      ;
  }
  else
  {
    old = millis() / 1000;
    oldReading = motor.getPosition();
    motor.setEffort(0);
    motor.reset();
  }
  */
}