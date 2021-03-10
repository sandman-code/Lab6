class PID
{
public:
    PID(double dt, double max, double min, double Kp, double Kd, double Ki);
    ~PID();
    double calculate(double setpoint, double pv);

private:
    double _dt;
    double _max;
    double _min;
    double _Kp;
    double _Kd;
    double _Ki;
    double _pre_error;
    double _integral;
};