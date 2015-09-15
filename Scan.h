#include <stdio.h>
#include <phidget21.h>
//#include <list>
#include <pthread.h>
#include <algorithm>
#include <vector>
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
  bool AnomaliesFound;
  int anomaly;
  int nearest_anomaly_location;
  int scancount;
  int scannedtimes;
  vector<int> Openning[72]; //vector stores IR readings
  unsigned int IRDiff;
  vector <int> AnomalyDistance;
  vector <int> AnomalyDirection;

  Scan(Servo &serv, Sonar &son, Halle &halleff, Moto &mot, Whisker &whl, Whisker &whr ) { //constructor
    servo=serv;
    sonar=son;
    hall=halleff;
    motor=mot;
    whleft=whl;
    whright=whr;
    seeBase = false;
	AnomaliesFound = false; 
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

	if (scannedtimes == 0 || scannedtimes > 2){ //If this is the first 180 scan, or a new 180 scan after a 360 scan, reset variables.
		AnomalyDistance.clear();
		AnomalyDirection.clear();
		AnomaliesFound = 0;
		anomaly = 0;
		scancount = 0;
		scannedtimes = 0;
	}

	Openning[0] = ir.getIRDistance(); //stores initial IR readings at extreme left
	
	//Moves servo in 5 degree increments from extreme left to right covering a span of 180 degrees.
    for(int i=1;i<37;i++) {
      while(servo.getPosition()<5*(i+1)) {
		servo.lookRight();
		wait(50);
	
		if(servo.getPosition()%60 == 0) {
		  wait(1000);
		  //take camera-shot logic
		}
      }
	  wait(100);

	  //Look for Opennings
	  scancount++;
	  Openning[scancount] = ir.getIRDistance();
	  IRDiff = Openning[scancount] - Openning[scancount-1];

	  if ( IRDiff > 1.25 * Openning [scancount] && AnomaliesFound == false){ //Choose 25%, needs to be tuned in practice, AnomaliesFound must be false or we will count the gaps twice.
		  
		// Increment Anomaly count, store IR Distance of anomaly 
		AnomalyDistance[anomaly] = ir.getIRDistance();
		AnomalyDirection[anomaly] = scancount;
		AnomaliesFound = true;
		anomaly++;
		}
	  
	  if ( IRDiff > 1.25 * Openning [scancount] && AnomaliesFound == true){ //So we don't double count the second edge of the same gap
		AnomaliesFound = false;
		}
	}

	servo.disconnect(); //or servo.disengage() ?
	
	//Returns the smallest IR value of the anomolies
	nearest_anomaly_location = std::min_element (AnomalyDistance.begin(), AnomalyDistance.end());
	
	//Returns the position of the nearest anomaly. 
	std::vector<int>::iterator it = std::find(AnomalyDistance.begin(), AnomalyDistance.end(), nearest_anomaly_location);
   
	//Stores the location of the nearest anomaly in nearest_anomol_location
	//returns 0 for N-E, 1 for N-W, 2 for S-E, 3 for S-W, 4 for direct north, 5 for direct south, 6 for direct east, 7 for direct west

	if (scannedtimes == 1){ //direction for a single 180 scan only
		if (AnomalyDirection[*it] < 5 && > 67){
			nearest_anomaly_location = 7;} //W
		else if (AnomalyDirection[*it] >= 5 && < 13){
			nearest_anomaly_location = 1;} //N-W
		else if (AnomalyDirection[*it] >= 13 && < 22){
			nearest_anomaly_location = 5;} //N
		else if (AnomalyDirection[*it] >= 22 && < 31){
			nearest_anomaly_location = 0;} //N-E
		else if (AnomalyDirection[*it] >= 31 && < 40){
			nearest_anomaly_location = 6;} //E
		else{// no anomaly 
			nearest_anomaly_location = 8;
			AnomaliesFound = false;}

	if (scannedtimes == 2){ //360 scan
		if (AnomalyDirection[*it] < 5 && > 67){
			nearest_anomaly_location = 7;} //W
		else if (AnomalyDirection[*it] >= 5 && < 13){
			nearest_anomaly_location = 1;} //N-W
		else if (AnomalyDirection[*it] >= 13 && < 22){
			nearest_anomaly_location = 5;} //N
		else if (AnomalyDirection[*it] >= 22 && < 31){
			nearest_anomaly_location = 0;} //N-E
		else if (AnomalyDirection[*it] >= 31 && < 40){
			nearest_anomaly_location = 6;} //E
		else if (AnomalyDirection[*it] >= 40 && < 49){
			nearest_anomaly_location = 3;} //SE
		else if (AnomalyDirection[*it] >= 49 && < 58) {
			nearest_anomaly_location = 5;} //S
		else if (AnomalyDirection[*it] >= 58  && <= 67){
			nearest_anomaly_location = 4;}
		else{// no anomaly 
			nearest_anomaly_location = 8;
			AnomaliesFound = false;}
	}
		//increments after each 180 scan is completed
		scannedtimes++;
  }

  void scan360(){
    scan180();
    Moto.turnRight(5000);
    scan180();
    Moto.turnRight(5000);
	//if camera detects base, update baseSeen to true
  }

  int lookLeft() {
  if(servo.getPosition()>1) {
    servo.lookleft();
    wait(500);
   } 
    //return IR-distance
  }

  int lookRight() {
  if(servo.getPosition<184) {
    while(servo.getPosition<185) {
      servo.lookright();
      wait(50);
    }
    }
    //return IR-distance


  int room() {
    //room detection logic here, returns room number here, this uses Webcam Image Recognition.
  }

  void align(int direction) { // align: 0 = align with right wall, 1 = align with left wall

  } 

  int nearestAnomaly() {
	  //scan360();
	  //IR-logic: finds nearest anomaly, returns 0 for N-E, 1 for N-W, 2 for S-E, 3 for S-W, 4 for direct north, 5 for direct south, 6 for direct east, 7 for direct west, 8 for no anomolies found
	  return nearest_anomaly_location; 
  }

  bool baseSeen() {
    return seeBase;
  }

  //could have obstacle avoidance in here as well as a last measure
  //e.g. while(scan.pathClear() == true) 
  //or maybe a separate obstacle avoidance thread/listener


};
