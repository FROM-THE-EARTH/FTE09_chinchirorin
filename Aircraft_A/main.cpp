#include "Avionics.h"

Avionics avionics;

static void defineFunctions();

int main()
{
  printf("Hello Mbed\r\n");

  defineFunctions();

  avionics.setDebugMode(true);

  avionics.initialize();

  avionics.begin();
}

static void defineFunctions()
{
  avionics.Condition_Launch = []() {
    return avionics.data().accel.length() > 2.5;
  };

  avionics.Condition_Detach = Function::Condition::None;

  avionics.Condition_Deceleration = Function::Condition::None;

  avionics.Condition_Landing = []() {
    return (avionics.data().time - avionics.data().bootTime) > 140.0f;
  };

  avionics.Operation_Detach = Function::Operation::None;

  avionics.Operation_OpenParachute = Function::Operation::None;
}