#include "Avionics/Avionics.h"

Avionics avionics;

DigitalOut igniter(p19, 1);
PwmOut servo_1(p21), servo_2(p22);
//ラズパイカメラ　p15 high -< low(カメラスタート) -> high(ストップ)

void defineFunctions();

#include "IM920SoftSerial.h"
IM920SoftSerial im920(p15, p16);

int main()
{
    while(1){
        im920.update();
        auto r = im920.received();
        if(r != ""){
            //printf("%s\r\n", r.c_str());
        }
    }
  /*defineFunctions();

  avionics.setDebugMode(true);

  if(!avionics.initialize()){
    printf("ERROR\r\n");
    return 0;
  }

  avionics.begin();*/
}
/*
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
    servo_1.pulsewidth(1.50/1000.0);//1 open
    servo_2.pulsewidth(1.60/1000.0);//2 open
  };

  avionics.Operation_CloseServo = [](){
    servo_1.pulsewidth(0.90/1000.0);//1 close
    servo_2.pulsewidth(0.90/1000.0);//2 close
  };
}
*/

/*#include "mbed.h"

#include "BufferedSoftSerial.h"

BufferedSoftSerial ss(p15, p16);

int main(){
  printf("HELLO WORLD\r\n");

  ss.baud(19200);
  bool reading = false;

  while(1){
    if(ss.readable()){
      printf("%c",static_cast<char>(ss.getc()));
      reading = true;
    }
    if(reading && !ss.readable()){
      printf("\r\n");
      reading = false;
    }
    
    if(!reading && !ss.readable()){
      printf("unreadable\r\n");
    }

    wait_us(500000);
  }
}*/