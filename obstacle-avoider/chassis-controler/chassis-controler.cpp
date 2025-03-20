#include "wheel-controler/wheel-controler.cpp"
#include <Arduino.h>

class ChasisControler{
private:
    WheelControler *left_wheel;
    WheelControler *right_wheel;
public: 
    int speed = 200;
    ChasisControler(WheelControler *left_wheel, WheelControler *right_wheel){
        this->left_wheel = left_wheel;
        this->right_wheel = right_wheel;
        config();
    };

    void front(){
        left_wheel->ride_front();
        right_wheel->ride_front();
    };

    void back(){
        left_wheel->ride_back();
        right_wheel->ride_back();
    };

    void left(){
        left_wheel->ride_back();
        right_wheel->ride_front();
    };

    void right(){
        left_wheel->ride_front();
        right_wheel->ride_back();
    };

    void start(){
        left_wheel->start();
        right_wheel->start();
        speed_control(speed);
    };

    void stop(){
        left_wheel->stop();
        right_wheel->stop();
    };

    void speed_control(int speed){
        this->speed = speed;
        int right_speed = speed * 235/255;
        left_wheel->speed_control(this->speed);
        right_wheel->speed_control(right_speed);
    };

    void config(){
        left_wheel->config();
        right_wheel->config();
    };
};
