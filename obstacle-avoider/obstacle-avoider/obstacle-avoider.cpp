#include "../chassis-controler/chassis-controler.cpp"
#include "../sensors-controler/sensors-controler.cpp"
#include "states.cpp"
#define TURN_SPEED 130
#define RIDE_SPEED 130


class ObstacleAvoider
{
private:
    ChasisControler *chasis;
    SensorsControler *sensors;
    states state = states::stop_front;

    void front()
    {
        if (this->sensors->check_front_obstacle() || this->sensors->check_left_obstacle())
        {
            this->state = states::stop_right;
        }
        else if (this->sensors->check_right_obstacle())
        {
            this->state = states::stop_left;
        }
        else
        {
            this->state = states::front;
            this->chasis->front();
            this->chasis->start();
        }
    }

    void stop_left()
    {
        this->chasis->stop();
        this->chasis->speed_control(TURN_SPEED);
        this->state = states::left;
        delay(500);
    }

    void stop_right()
    {
        this->chasis->stop();
        this->chasis->speed_control(TURN_SPEED);
        this->state = states::right;
        delay(500);
    }

    void stop_front()
    {
        this->chasis->stop();
        this->chasis->speed_control(RIDE_SPEED);
        this->state = states::front;
        delay(500);
    }

    void left()
    {
        if (this->sensors->check_front_obstacle() || this->sensors->check_left_obstacle() || this->sensors->check_right_obstacle())
        {
            this->chasis->start();
            this->chasis->left();
            this->state = states::left;
        }
        else
        {
            this->state = states::stop_front;
        }
    }

    void right()
    {  
        if (this->sensors->check_front_obstacle() || this->sensors->check_left_obstacle() || this->sensors->check_right_obstacle())
        {
             this->chasis->start();
            this->chasis->right();
            this->state = states::right;
        }
        else
        {
            this->state = states::stop_front;
        }
    }

public:
    ObstacleAvoider(ChasisControler *chasis, SensorsControler *sensors)
    {
        this->chasis = chasis;
        this->sensors = sensors;
    };

    void ride()
    {
        switch (this->state)
        {
        case states::front:
            front();
            break;
        case states::left:
            left();
            break;
        case states::right:
            right();
            break;
        case states::stop_left:
            stop_left();
            break;
        case states::stop_right:
            stop_right();
            break;
        case states::stop_front:
            stop_front();
            break;
        default:
            digitalWrite(LED_BUILTIN, HIGH);
            this->chasis->stop();
            break;
        }
    }
};
