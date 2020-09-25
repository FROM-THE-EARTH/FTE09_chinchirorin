/*
This program is developed under the mbed-os 6.2.0
*/

#include "Aircraft.h"

constexpr float launchThreshold = 2.5;    // G
constexpr float landingTime = 140 * 1000; // ms
constexpr float basePressure = 1015.0;    // Pa

// modules
IM920Wrapper receiver("Receiver_A",p28, p27, p29, p30);
IM920Wrapper transmitter("Sender_A", p28, p27, p29, p30);
LPSWrapper lps331("LPS331_A", p9, p10, LPS331_I2C_SA0_HIGH);
LSMWrapper lsm("LSM9DS1_A", p9, p10);
// SDFileSystem sd(p5, p6, p7, p8, "sd");
// DigitalIn flightPin(p12);
// PwmOut servo_1(p21), servo_2(p22), servo_3(p23);

Aircraft aircraft(launchThreshold, landingTime, basePressure, &receiver, &transmitter,
                   &lps331, &lsm);

int main()
{

  aircraft.setDebugMode(true);

  aircraft.initialize();

  aircraft.begin();
}
