/*
This program is developed under the mbed-os 6.2.0
*/

#include "Aircraft.h"

constexpr float launchThreshold = 2.5;    // G
constexpr float landingTime = 140 * 1000; // ms

Aircraft aircraft(launchThreshold, landingTime);

int main() {
  printf("Hello Mbed\r\n");

  aircraft.setDebugMode(true);

  aircraft.initialize();

  aircraft.begin();
}
