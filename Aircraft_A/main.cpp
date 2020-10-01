#include "Aircraft.h"

//condition
constexpr float launchThreshold = 2.5; // G
constexpr float landingTime = 140;     // s

Aircraft aircraft(launchThreshold, landingTime);

int main()
{
  printf("Hello Mbed\r\n");

  aircraft.setDebugMode(true);

  aircraft.initialize();

  aircraft.begin();
}
