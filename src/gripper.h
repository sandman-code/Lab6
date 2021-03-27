#pragma once

#include <servo32u4.h>
#include <Romi32U4.h>

class gripper
{
public:
    void operate(bool closed);
    bool isPanel();
    void initilize();

private:
    Servo32U4 servo;
    bool closed = false;
};