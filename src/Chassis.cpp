#include "Chassis.h"
#include <Arduino.h>
#include <Romi32U4Encoders.h>
float lastreading = 0;

enum States
{
    start,
    forward,
    turn,
    stop
} state1;

void Chassis::initilize()
{
    state1 = forward;
}
//drives the robot a certian amount of inches forward
//drives the robot a certian amount of inches forward
void Chassis::driveDistance(float inches)
{
    lastreading = encoders.getCountsAndResetLeft();   //grabs the current position of the wheel and resets the encoder to ensure
    lastreading = encoders.getCountsLeft();           //in order the limit of the encoder will not be reached
    double convertion = (wheelDiameter * 3.14) / CPR; //convert the inches given into tick marks for wheel encoders
    targetCount = (inches / convertion) + lastreading;
    motors.setEfforts(100, 100); //moves the fobot forward and stores new speed
    leftEffort = 100;
    rightEffort = 100;
}

//returns true if the left wheel has reached the distance it should rotate
bool Chassis::doneDriving()
{
    if (encoders.getCountsLeft() >= targetCount)
    {
        return true;
    }
    return false;
}

//turns the robot a certian amount of degrees
void Chassis::turnAngle(float degrees)
{
    float absdegree = abs(degrees);
    lastreading = encoders.getCountsLeft();           //saves current wheel positions
    double convertion = (wheelDiameter * 3.14) / CPR; //converts degrees given inot ticks marks wheel should rotatae subtracting 30 rotations inorder to reach the desidered degree
    double convertion2 = (wheelTrack * 3.15) / convertion;
    targetCount = (absdegree / 360) * convertion2 + lastreading - 30;
    if (degrees >= 0)
    {
        motors.setEfforts(100, -100); //starts turning robot and saving current speed/direction of wheels
        leftEffort = 100;
        rightEffort = -100;
    }
    else
    {
        motors.setEfforts(-100, 100);
        leftEffort = -100;
        rightEffort = 100;
    }
    Serial.println(absdegree);
}

//stops the robot
void Chassis::pauseDriving()
{
    motors.setEfforts(0, 0);
}

//resumes the robot from where it left off
void Chassis::resumeDriving()
{
    motors.setEfforts(leftEffort, rightEffort);
}

bool Chassis::turnLeftRight(bool left)
{
    Chassis move;

    switch (state1)
    {
    case start:
        move.driveDistance(3);
        state1 = forward;
        break;
    case forward:
        if (move.doneDriving())
            state1 = turn;
        break;
    case turn:
        if (left)
        {
            move.turnAngle(-100);
            state1 = stop;
        }
        if (!left)
        {
            move.turnAngle(100);
            state1 = stop;
        }
        break;

    case stop:
        if (move.doneDriving())
        {
            state1 = start;
            move.pauseDriving();
            return true;
        }
        break;
    }
    return false;
}