#include <stdio.h>
#include <pthread.h>
#include <phidget21.h>
#include "Servo.h"

int main(int argc, char* argv[])
{
  Servo servo;
  printf("Min: %f, Max: %f\n", servo.getPositionMin(), servo.getPositionMax());
  printf("Woo\n");
  servo.disconnect();
  servo.engage();
  while(true){
    servo.lookright();
    sleep(1);
    /*while(servo.getPosition()<185)
      {
      }*/
    servo.lookleft();
    sleep(1);
    /*while(servo.getPosition()>0)
      {
      }*/
  }
  printf("Woo\n");
  getchar();
  printf("Pos: %f\n", servo.getPosition());
  return 0;
};
