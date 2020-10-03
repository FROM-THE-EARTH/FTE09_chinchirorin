#include "Aircraft.h"

Aircraft aircraft;

static void defineFunctions();

int main()
{
  printf("Hello Mbed\r\n");

  defineFunctions();

  aircraft.setDebugMode(true);

  aircraft.initialize();

  aircraft.begin();
}

static void defineFunctions()
{
  aircraft.Condition_Launch = []() {
    return aircraft.data().accel.length() > 2.5;
  };

  aircraft.Condition_Detach = Function::Condition::None;

  aircraft.Condition_Deceleration = Function::Condition::None;

  aircraft.Condition_Landing = []() {
    return (aircraft.data().time - aircraft.data().bootTime) > 140.0f;
  };

  aircraft.Operation_Detach = Function::Operation::None;

  aircraft.Operation_OpenParachute = Function::Operation::None;
}