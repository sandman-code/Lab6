#include "BlueMotor.h"
#include <Romi32U4.h>
#include <PID.h>
// variables for the counter of controlling the encoder
const char X = 5;
int errorCount = 0;
int oldValue = 0;
long count = 0;
const int DBdiff = 40;
char encoderArray[4][4] = {
    {0, 1, -1, X},
    {-1, 0, X, 0},
    {1, X, 0, -1},
    {X, -1, 1, 0}};
// the differnt sates for the move to function
enum States
{
    Start,
    clockwise,
    counterclockwise,
    stop
} armState;

PID controlPID(400.0, -400.0, 25, 20, 10);

//initilizes all the pins and the interupts
void Bluemotor::initilize()
{ //outputs and inputs to controller the blue motor
    pinMode(PWM, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
    motors.setEfforts(0, 0);

    //interupts to count the encoder
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), isr, CHANGE);

    //initlize the differnt states
    armState = Start;
};

//The intrupt service routune
void Bluemotor::isr()
{ //shifts the bits left deping on the reading of the second pin, looks up the value in the array
    int newValue = (digitalRead(3) << 1) | digitalRead(2);
    char value = encoderArray[oldValue][newValue];

    //if the number changed add or subtract, or if the value did not change add add one to errorcount
    if (value == X)
    {
        errorCount++;
    }
    else
    {
        count -= value;
    }
    oldValue = newValue;
}

//will change the mover the motor clockwiseor counterclockwise and adjust the speed
void Bluemotor::setEffort(int effort, bool clockwise)
{
    //turn clockwise
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }

    //do not turn
    else if (effort == 0)
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }

    //turn counter clockwise
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }

    //validaadates the effort number and sends a PWM to the motor
    int value = constrain(effort, 0, 400);
    OCR1C = value;
}

//sorts the inital effort for direction and speed
void Bluemotor::setEffort(int effort)
{

    //turn clockwise
    if (effort < 0)
    {
        setEffort(-effort, true);
    }
    //turn counterclockwise or stop
    else
    {
        setEffort(effort, false);
    }
}

void Bluemotor::setEffortWithoutDB(int effort)
{

    //turn clockwise
    if (effort < 0)
    {
        setEffortWithoutDB(-effort, true);
    }
    //turn counterclockwise or stop
    else
    {
        setEffortWithoutDB(effort, false);
    }
}
//reports back the position of the motor
long Bluemotor::getPosition()
{
    return count;
}

//resets the position count of the encouder to count that as the new base position
void Bluemotor::reset()
{
    count = 0;
}

void Bluemotor::setEffortWithoutDB(int effort, bool clockwise)
{
    //turn clockwise
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }

    //do not turn
    else if (effort == 0)
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }

    //turn counter clockwise
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }

    //validaadates the effort number and sends a PWM to the motor
    int value = constrain(effort + DBdiff, 0, 400);
    Serial.println(value);
    OCR1C = value;
}

//moves the mover a certion amount depening on the position input
void Bluemotor::moveTo(long position)
{ //initlizes a Bluemotor varible and grabs the current posiotn of the encoder
    setEffortWithoutDB(controlPID.calculate(position, getPosition()));
}

void Bluemotor::goToRelease()
{
    moveTo(7250);
}

void Bluemotor::goTo45()
{
    moveTo(3590);
}

void Bluemotor::goTo25()
{
    moveTo(7260);
}

void Bluemotor::home()
{
    Bluemotor blue;
    if (digitalRead(limit))
        blue.setEffort(0);
    else
    {
        blue.setEffort(-200);
    }
    count = 0;
}