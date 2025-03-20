#include "distance-sensor-controler/distance-sensor-controler.cpp"

class SensorsControler
{
public:
    DistanceSensorControler *left_sensor;
    DistanceSensorControler *right_sensor;
    DistanceSensorControler *front_sensor;
    SensorsControler(DistanceSensorControler *left_sensor, DistanceSensorControler *right_sensor, DistanceSensorControler *front_sensor)
    {
        this->left_sensor = left_sensor;
        this->right_sensor = right_sensor;
        this->front_sensor = front_sensor;
    };

    bool check_front_obstacle()
    {
        return front_sensor->get_distance_in_cm() < 15;
    };

    bool check_left_obstacle()
    {
        return left_sensor->get_distance_in_cm() < 10;
    };

    bool check_right_obstacle()
    {
        return right_sensor->get_distance_in_cm() < 10;
    };
};
