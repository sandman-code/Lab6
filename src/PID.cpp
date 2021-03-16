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
}

PID::~PID() {}

double PID::calculate(long setpoint, long pv)
{
    // Get dt
    now = millis();
    long _dt = now - _last_time;

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
}