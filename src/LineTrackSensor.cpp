#include "LineTrackSensor.h"
#include <Distance.h>

LineTrackSensor::LineTrackSensor()
{
    pinMode(LINE_LEFT, INPUT);
    pinMode(LINE_RIGHT, INPUT);
}

float LineTrackSensor::getValue()
{
    return analogRead(LINE_LEFT);
}

float LineTrackSensor::getLeft()
{
    return analogRead(LINE_LEFT);
}

float LineTrackSensor::getRight()
{
    return analogRead(LINE_RIGHT);
}

float LineTrackSensor::calcError()
{
    return getRight() - getLeft();
}

bool LineTrackSensor::checkStopped()
{
    return (getLeft() > 550) && (getRight() > 550);
}

bool LineTrackSensor::follow()
{
    if (farSensor.getDistance() <= goal)
    {
        motors.setLeftEffort(0);
        motors.setRightEffort(0);
        return true;
    }
    else if (!checkStopped())
    {
        motors.setLeftEffort(50 + calcError());
        motors.setRightEffort(50 - calcError());
        Serial.println(getRight());
    }
    else
    {
        motors.setLeftEffort(0);
        motors.setRightEffort(0);
    }
    return false;
}
void LineTrackSensor::pause()
{
    motors.setEfforts(0, 0);
}

void LineTrackSensor::resume()
{
    LineTrackSensor sense;
    sense.follow();
}