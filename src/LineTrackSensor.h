#pragma once

#include <Romi32U4.h>
#include <Romi32U4Motors.h>
#include <Distance.h>

class LineTrackSensor
{
public:
    LineTrackSensor();
    float getValue();
    float getLeft();
    float getRight();
    float calcError();
    bool checkStopped();
    bool follow();
    Romi32U4Motors motors;
    int goal;
    void pause();
    void resume();

private:
    const int LINE_LEFT = 20;
    const int LINE_RIGHT = 21;
    const int Kp = 10;
    Distance farSensor;
};