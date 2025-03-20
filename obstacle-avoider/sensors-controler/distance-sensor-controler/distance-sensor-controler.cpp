#include <Arduino.h>

class DistanceSensorControler
{
private:
    int trig_pin;
    int echo_pin;

public:
    DistanceSensorControler(int trig_pin, int echo_pin)
    {
        this->trig_pin = trig_pin;
        this->echo_pin = echo_pin;
        config();
    };

    int get_distance_in_cm()
    {
        digitalWrite(trig_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(trig_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_pin, LOW);
        digitalWrite(echo_pin, HIGH);
        int time = pulseIn(echo_pin, HIGH);
        return time / 58;
    };

    void config()
    {
        pinMode(trig_pin, OUTPUT);
        pinMode(echo_pin, INPUT);
    };
};
