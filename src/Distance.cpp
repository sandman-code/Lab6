#include <Distance.h>

long timeLeft = 0;
long begin = 0;
int flag = 0;
int distance = 0;

//initlizes pin assigment
void Distance::initilize()
{
    pinMode(0, INPUT);
}

//reads back current distance pulse within 2 milliseconds max
double Distance::getDistance()
{
    time = pulseIn(0, HIGH, 20000);
    distance = (time - 1000) * 3 / 4;
    return (distance);
}