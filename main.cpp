#include "Avionics/Avionics.h"

Avionics avionics;

PwmOut servo_1(p21), servo_2(p22);
DigitalOut raspi(p20, 1);


void defineFunctions();


int main()
{
  raspi = 1;

  defineFunctions();

  avionics.setDebugMode(true);

  avionics.initialize();

  avionics.begin();
}


void defineFunctions()
{
  avionics.Condition_Launch = []() {
    return (avionics.data().accel.length() > 2.5f);
  };

  avionics.Condition_Deceleration = [](){
    const bool detectTop = (avionics.data().maxAltitude - avionics.data().altitude) > 10.0f;
    const bool timeout = (avionics.data().time - avionics.data().launchTime) > 28.0f;
    return detectTop || timeout;
  };

  avionics.Condition_Landing = []() {
    return (avionics.data().time - avionics.data().decelerationTime) > 120.0f;
  };

  avionics.Operation_OpenParachute = [](){
    servo_1.pulsewidth(1.50/1000.0);
    servo_2.pulsewidth(1.60/1000.0);
  };

  avionics.Operation_CloseServo = [](){
    servo_1.pulsewidth(0.90/1000.0);
    servo_2.pulsewidth(0.90/1000.0);
  };

  avionics.Operation_CameraOn = [](){
    raspi = 0;
  };

  avionics.Operation_CameraOff = [](){
    raspi = 1;
  };
}