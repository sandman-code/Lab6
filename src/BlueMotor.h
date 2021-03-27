#pragma once

#include <Romi32U4.h>
#include <Romi32U4Encoders.h>

class Bluemotor
{
public:
    void initilize();
    void setEffort(int effort);
    void setEffortWithoutDB(int effort);
    void moveTo(long position);
    long getPosition();
    void reset();
    void home();
    void goToRelease();
    void goTo45();
    void goTo25();

    //Chassis();

private:
    Romi32U4Motors motors;
    void setEffort(int effort, bool clockwise);
    void setEffortWithoutDB(int effort, bool clockwise);
    static void isr();
    const unsigned PWM = 11;
    const int AIN2 = 4;
    const int AIN1 = 13;
    const int ENCA = 2;
    const int ENCB = 3;
    const int limit = 12;
};