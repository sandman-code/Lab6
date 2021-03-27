#include "PID.h"
#include <Romi32U4.h>

PID::PID(double max, double min, double Kp, double Kd, double Ki)
{
    // Inits all error coefficients for the PID
    _max = max;
    _min = min;
    _Kp = Kp;
    _Kd = Kd;
    _Ki = Ki;
    long lastError = 0;
    long previousTime = 0;
}

PID::~PID() {}

long PID::calculate(long setpoint, long pv)
{

    long currentTime = millis();
    long elapsedTime = currentTime - previousTime;

    long error = setpoint - pv;

    long cumError = 0;
    cumError += error * elapsedTime;

    long rateError = (error - lastError) / elapsedTime;

    long output = _Kp * error + _Ki * cumError + _Kd * rateError;

    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;

    lastError = error;
    previousTime = currentTime;

    return output;
    /*
    // Get dt
    now = millis();
    long _dt = 1;

    // Calculate error
    double error = setpoint - pv;

    // Proportional term
    double Pout = _Kp * error;

    // Integral term
    _integral += error * _dt;
    double Iout = _Ki * _integral;

    // Derivative term
    double derivative = (error - _pre_error) / _dt;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Restrict to max/min
    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;

    // Save error to previous error
    _pre_error = error;

    // Update time
    _last_time = now;

    return output;
    */
}