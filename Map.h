#include <stdio.h>
#include "Scan.h"
#include "Moto.h"
#include "Servo.h"
#include "Sonar.h"

class Map {

public:

  bool baseSeen;
  int baseRoomNumber;
  int startingRoom;
  int currentRoom;
  Scan scan;
  Moto moto;
  Sonar sonar;
  Servo servo;

  /*

|---------------------|
|     3    |     2    |
|          |          |
|    -------   -------|
|          5	      |
|--------   -------   |
|     0	    |	1     |		
|	    |         |
|---------------------|
  */

  Map(Scan &sc, Moto &mot, Sonar &son, Servo &serv) {
    baseSeen=false;
    baseRoomNumber=0;
    currentRoom=0;
    startingRoom=0;
    scan =sc;
    moto=mot;
    sonar=son;
    servo=&serv;

  }

  void setBase(int baseloc) {
    baseRoomNumber=baseloc;
  }

  void setStartingRoom(int startRoom) {
    startingRoom=startRoom;
  }

  //moves through a door after scan has told it which quadrant the door is in
  void moveThroughDoor() {
    if(scan.nearestAnomaly() == 0) { //door in N-E
      while(sonar.state()==0) {
	moto.forwards();
    }
      moto.stop();
      moto.right(2500);
      while(scan.lookLeft()<=20){
	moto.forwards();
      }
      moto.stop();
      //IR-logic here while(distance<something), maybe alignment too
      moto.left(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 1) { //door in N-W
      while(sonar.state()==0) {
	moto.forwards();
      }
      moto.stop();
      moto.left(2500);
       while(scan.lookRight()<=20){
	moto.forwards();
      }
      moto.stop();
      //IR-logic here while(distance<something), maybe alignment too
      moto.right(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 2) { //door in S-E
   moto.right(5000);
   while(sonar.state()==0) {
	moto.forwards();
      }
      moto.stop();
      moto.left(2500);
      while(scan.lookRight()<=20){
	moto.forwards();
      }
      moto.stop();
      //IR-logic here while(distance<something), maybe alignment too
      moto.right(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 3) { //door in S-W
   moto.right(5000);
   while(sonar.state()==0) {
	moto.forwards();
    }
      moto.stop();
      moto.right(2500);
       while(scan.lookLeft()<=20){
	moto.forwards();
      }
      moto.stop();
      //IR-logic here while(distance<something) -> moto.forwards() , maybe alignment too
      moto.left(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 4) { // door hard north, alignment should have put robot far away enough from wall
      while(scan.lookRight()<=20) {
	if(sonar.state()==0) { //need this because might be in room 1 or 3 where there is a right angle after the exit
	  moto.forwards();
	} else {
	  break;}
      }
      moto.stop();
    } 
    if(scan.nearestAnomaly() == 5) { // door hard south, alignment should have put robot far away enough from wall
      moto.right(5000);
     while(scan.lookRight()<=20) {
	if(sonar.state()==0) {
	  moto.forwards();
	} else {
	  break;}
      }
      moto.stop();
      //IR-logic here while something moto.forwards();
    } 
    if(scan.nearestAnomaly() == 6) { // door hard east, alignment should have put robot far away enough from wall
      moto.right(2500);  
      while(scan.lookRight()<=20) {
	if(sonar.state()==0) {
	  moto.forwards();
	} else {
	  break;}
      }
      moto.stop();
      //IR-logic here while something moto.forwards();
    } 
    if(scan.nearestAnomaly() == 7) { // door hard west, alignment should have put robot far away enough from wall
      moto.left(2500);
      while(scan.lookRight()<=20) {
	if(sonar.state()==0) {
	  moto.forwards();
	} else {
	  break;}
      }
      moto.stop();
      //IR-logic here while something moto.forwards();
    } 

  }

  void goHome(){
    if(startingRoom == baseRoomNumber){
      moveThroughDoor();
      moto.right(5000);
      moto.forwards(6000);
      scan.Scan360();
      moto.right(1250);
      moto.forwards(8000);
      return;
    }

    if (startingRoom == 0){
	printf("Robot is in room 0 \n");
	currentRoom = 0;
	moveThroughDoor();
	if (baseRoomNumber == 1) {
		moto.right(2500);
		moto.forwards(6000);
		scan.align(0);//align with the right wall
		while (scan.lookRight() <= 20 || sonar.state() == 0) { //might need calibration
			moto.forwards();
		}
			moto.stop();
			moto.right(2500);
			moto.forwards(4000);
			scan.align(1);//align with left wall
			currentRoom = 1;
			scan.scan360();
		     
			if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
			  moto.right(1250);
			  moto.forwards(8000);
				return;
			}
		
	}

	if (baseRoomNumber == 2) {
	  moto.right(2500);
		while (scan.lookLeft() <= 20) {
			moto.forwards();
		}
		moto.stop();
		moto.left(2500);
		moto.forwards(4000);
		scan.align(1); //align with left wall
		currentRoom = 2;
		scan.scan360();
       		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
			return;
		}
	}

	if (baseRoomNumber == 3) {
	  moto.left(2500);
		scan.align(0);
		while (scan.lookRight() <= 20 || sonar.state()==0){
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		moto.align(1);
		currentRoom = 3;
		scan.scan360();
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {	    	
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

}

if (startingRoom == 1) {
	printf("Robot is in room 1 \n");
	currentRoom = 1;
	moveThroughDoor();
	if (baseRoomNumber == 0) {
	  moto.left(2500);
	  scan.align(0); //align with right wall
	  moto.forwards(6000);
	  While(scan.lookLeft() <= 20) {
	    moto.forwards();
	  }
		moto.stop();
		moto.left(2500);
		moto.forwards(4000);
		scan.align(1); //align with left wall
		currentRoom = 0;
		scan.scan360();
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

	if (baseRoomNumber == 2) {
	  moto.left(2500);
		scan.align(0);
		While(scan.lookRight() <= 20) {
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 2;
		scan.scan360();
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

	if (baseRoomNumber == 3) {
	  moto.left(2500);
	  scan.align(0);
	  moto.forwards(6000);
		While(scan.lookLeft() <= 20) {
			moto.forwards();
		}
		moto.stop();
		scan.align(0);
		while(scan.lookRight() <= 20 || sonar.state()==0){
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 3;
		scan.scan360();
		
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);	
		  return;
		}
	}
}


if (startingRoom == 2) {
	printf("Robot is in room 2 \n");
	currentRoom = 2;
	moveThroughDoor();
	if (baseRoomNumber == 3) {
	  moto.right(2500);
		moto.forwards(6000);
		scan.align(0);
		while (scan.lookRight() <= 20 || sonar.state() == 0) {
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 3;
		scan.scan360();
		
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}

	}

	if (baseRoomNumber == 0) {
		moto.right(2500);
		while (scan.lookLeft() <= 20) {
			moto.forwards();
		}
		moto.stop();
		moto.left(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 0;
		scan.scan360();
		
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

	if (baseRoomNumber == 1) {
		moto.left(2500);
		scan.align(0);
		while (scan.lookRight() <= 20 || sonar.state() == 0){
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 1;
		scan.scan360();
		
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

}

if (startingRoom == 3) {
	printf("Robot is in room 3 \n");
	currentRoom = 3;
	moveThroughDoor();
	if (baseRoomNumber == 2) {
		moto.left(2500);
		scan.align(0);
		moto.forwards(6000);
		While(scan.lookLeft() <= 20) {
			moto.forwards();
		}
		moto.stop();
		moto.left(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 2;
		scan.scan360();
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

	if (baseRoomNumber == 0) {
		moto.left(2500);
		scan.align(0);
		While(scan.lookRight() <= 20) {
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 0;
		scan.scan360();
		
		if (scan.baseSeen() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

	if (baseRoomNumber == 1) {
		moto.left(2500);
		scan.align(0);
		moto.forwards(6000);
		While(scan.lookLeft() <= 20) {
			moto.forwards();
		}
		moto.stop();
		scan.align(0);
		while (scan.lookRight <= 20 || sonar.state() == 0){
			moto.forwards();
		}
		moto.stop();
		moto.right(2500);
		moto.forwards(4000);
		scan.align(1);
		currentRoom = 1;
		scan.scan360();
		
		if (scan.seeBase() == true && currentRoom == baseRoomNumber) {
		  moto.right(1250);
		  moto.forwards(8000);
		  return;
		}
	}

 }
  }

};
