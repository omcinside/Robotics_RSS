#include <stdio.h>
#include <phidget21.h>
//#include <list>
#include <pthread.h>
#include <libpowerbutton.h>
#include "Whisker.h"
#include "HallE.h"
#include "Moto.h"
#include "Sonar.h"
#include "Servo.h"
#include "wait.h"

class Scan {

 public:

  Servo servo;
  Sonar sonar;
  HallE hall;
  Moto motor;

  Whisker whleft;
  Whisker whright;

  bool seeBase;

  Scan(Servo &serv, Sonar &son, Halle &halleff, Moto &mot, Whisker &whl, Whisker &whr ) { //constructor
    servo=serv;
    sonar=son;
    hall=halleff;
    motor=mot;
    whleft=whl;
    whright=whr;
    seeBase = false;
  }


  void scan180(){ // 3 camera shots, 37 IR points
    servo.disconnect();
    servo.engage();
    while(servo.getPosition()<220) { //puts the servo at 0
      servo.lookLeft();
      wait(50); //50ms wait for accuracy
    }
    wait(1000);
    //do some scans

    for(int i=0;i<37;i++) {
      while(servo.getPosition()<5*(i+1)) {
	servo.lookRight();
	
	wait(50);
	if(servo.getPosition()%60 == 0) {
	  wait(1000);
	  //take camera-shot logic
	}
      }

      wait(100);
      //IR-logic
    }

    servo.disconnect(); //or servo.disengage() ?
  }

  void scan360(){
    scan180();
    Moto.turnRight(5000);
    scan180();
    Mot.turnRight(5000);

    //if camera detects base, update baseSeen to true
  }

  int lookLeft() {
    servo.lookleft();
    wait(500);
    //return IR-distance
  }

  int lookRight() {
    while(servo.getPosition<185) {
      servo.lookright();
      wait(50);
    }
    //return IR-distance


  int room() {
    //room detection logic here, returns room number here
  }

  void align(int direction) { // align: 0 = align with right wall, 1 = align with left wall
  } 

  int nearestAnomaly() {
    //IR-logic: finds nearest anomaly, returns 0 for N-E, 1 for N-W, 2 for S-E, 3 for S-W, 4 for direct north, 5 for direct south, 6 for direct east, 7 for direct west
  }

  bool baseSeen() {
    return seeBase;
  }

  //could have obstacle avoidance in here as well as a last measure
  //e.g. while(scan.pathClear() == true) 
  //or maybe a separate obstacle avoidance thread/listener


};
