#include <gripper.h>
#include <Romi32U4Motors.h>
#include <Romi32U4.h>

void gripper::initilize()
{
    pinMode(A0, INPUT);
    servo.Init();
    servo.Attach();
    servo.SetMinMaxUS(500, 2500);
}

void gripper::operate(bool closed)
{
    if (closed)
    {
        servo.Write(500);
    }
    else
    {
        servo.Write(2500);
        }
}

bool gripper::isPanel()
{
    if (analogRead(A0) <= 89)
        return false;
    else
    {
        return true;
    }
}