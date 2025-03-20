#include <Arduino.h>

class WheelControler{
private:
    int direction_pin;
    int brake_pin;
    int speed_pin;
    int speed;
public:
    
    WheelControler(int direction, int brake, int speed_pin, int speed){
        this->direction_pin = direction;
        this->brake_pin = brake;
        this->speed_pin = speed_pin;
        this->speed = speed;
        config();
    };

    void ride_front(){
        digitalWrite(direction_pin, HIGH);
    };

    void ride_back(){
        digitalWrite(direction_pin, LOW);
    };

    void stop(){
        digitalWrite(brake_pin, HIGH);
        speed_control(0);
        
    };

    void start(){
        digitalWrite(brake_pin, LOW);
        speed_control(this->speed);

    };

    void speed_control(int speed){
        this->speed = speed;
        analogWrite(speed_pin, this->speed);
    };

    void config(){
        pinMode(direction_pin, OUTPUT);
        pinMode(brake_pin, OUTPUT);
        pinMode(speed_pin, OUTPUT);
    }
};