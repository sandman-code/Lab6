class PID
{
public:
    PID(double max, double min, double Kp, double Kd, double Ki);
    ~PID();
    double calculate(double setpoint, double pv);
    unsigned long now;

private:
    double _max;
    double _min;
    double _Kp;
    double _Kd;
    double _Ki;
    unsigned long _last_time;
    double _pre_error;
    double _integral;
};