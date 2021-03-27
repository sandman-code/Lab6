#pragma

class PID
{
public:
    PID(double max, double min, double Kp, double Kd, double Ki);
    ~PID();
    long calculate(long setpoint, long pv);
    unsigned long now;
    double _max;
    double _min;
    double _Kp;
    double _Kd;
    double _Ki;
    unsigned long _last_time;
    double _pre_error;
    double _integral;
    long lastError = 0;
    long previousTime = 0;
};