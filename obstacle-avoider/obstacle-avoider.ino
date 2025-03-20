#include "constants.h"
#include "obstacle-avoider/obstacle-avoider.cpp"
#include <Arduino.h>

ObstacleAvoider *obstacle_avoider;
SensorsControler *sensors;
ChasisControler *chasis;

void setup()
{
  WheelControler *left_wheel = new WheelControler(DIRECTION_LEFT, BRAKE_LEFT, SPEED_LEFT, 200);
  WheelControler *right_wheel = new WheelControler(DIRECTION_RIGHT, BRAKE_RIGHT, SPEED_RIGHT, 200);
  chasis = new ChasisControler(left_wheel, right_wheel);
  DistanceSensorControler *left_sensor = new DistanceSensorControler(TRIG_LEFT, ECHO_LEFT);
  DistanceSensorControler *right_sensor = new DistanceSensorControler(TRIG_RIGHT, ECHO_RIGHT);
  DistanceSensorControler *front_sensor = new DistanceSensorControler(TRIG, ECHO);
  sensors = new SensorsControler(left_sensor, right_sensor, front_sensor);
  obstacle_avoider = new ObstacleAvoider(chasis, sensors);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  obstacle_avoider->ride();
  delay(10);
}
