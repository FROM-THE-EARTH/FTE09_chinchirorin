/*#include "Avionics/Avionics.h"

Avionics avionics;

DigitalOut igniter(p19, 1);
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
*/


#include "mbed.h"
#include "IM920.h"
 
DigitalOut myled(LED1);
BufferedSerial pc(USBTX, USBRX);
IM920 im920(p28, p27, p29, p30);
 
void callback () {
    int i;
    char buf[65];
 
    i = im920.recv(buf, 64);
    buf[i] = 0;
    printf("recv: '%s' (%d)\r\n", buf, i);
}
 
int main() {
    int i = 0;
    char buf[65];
 
    pc.set_baud(9600);
    pc.write("*** IM920\r\n", 12);
    im920.init();
    im920.attach(callback);
    myled = 1;
 
    for (;;) {
        im920.poll();
        if (pc.readable()) {
            char c;
            pc.read(&c, 1);
            if (c == '\r') {
                buf[i] = 0;
                printf("send: %s\r\n", buf);
                im920.send(buf, i);
                i = 0;
            } else
            if (i < 64) {
                buf[i] = c;
                i ++;
            }
        }
    }
}
 