#pragma once

#include <Romi32U4.h>
#include <Romi32U4Encoders.h>

class Distance
{
public:
    void initilize();
    double getDistance();

private:
    int time = 0;
};