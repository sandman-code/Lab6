#pragma once
#include <Arduino.h>
#include <Romi32U4.h>
#include <Romi32U4Encoders.h>

class Chassis
{
public:
    void driveDistance(float inches);
    bool doneDriving();
    void turnAngle(float angle);
    void pauseDriving();
    void resumeDriving();
    bool turnLeftRight(bool left);
    void initilize();
    //Chassis();

private:
    Romi32U4Motors motors;
    Romi32U4Encoders encoders;
    int leftEffort, rightEffort;
    const unsigned CPR = 1440;
    const float wheelDiameter = 2.8;
    const float wheelTrack = 5.75;
    long targetCount;
    float lastreading;
};