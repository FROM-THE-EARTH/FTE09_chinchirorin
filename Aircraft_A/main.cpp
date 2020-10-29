#include "Avionics/Avionics.h"

Avionics avionics;

DigitalOut igniter(p20, 0);
PwmOut servo_1(p21), servo_2(p23);//p21, p23

void defineFunctions();

int main()
{
  
  printf("Hello Mbed\r\n");

  defineFunctions();

  avionics.setDebugMode(true);

  avionics.initialize();

  avionics.begin();
}

void defineFunctions()
{
  avionics.Condition_Launch = []() {
    return (avionics.data().accel.length() > 2.5);
  };

  avionics.Condition_Detach = [](){
    return (avionics.data().time - avionics.data().launchTime) > 7.0f;
  };

  avionics.Condition_Deceleration = [](){
    return (avionics.data().time - avionics.data().launchTime) > 140.0f;
  };

  avionics.Condition_Landing = []() {
    return (avionics.data().time - avionics.data().bootTime) > 140.0f;
  };

  avionics.Operation_Detach = [](){
    igniter = 1;
  };

  avionics.Operation_OpenParachute = [](){
    //servo
  };

  avionics.Operation_CloseServo = [](){
    servo_1.pulsewidth(2.20/1000.0);//ms/1000 0.80
    servo_2.pulsewidth(2.20/1000.0);//ms/1000 0.80
  };
}
