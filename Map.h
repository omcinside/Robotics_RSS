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

  void setCurrentRoom(int currRoom) {
    currentRoom=currRoom;
  }

  void setStartingRoom(int startRoom) {
    startingRoom=startRoom;
  }

  //moves through a door after scan has told it which quadrant the door is in
  void moveThroughDoor() {
    if(scan.nearestAnomaly() == 0) { //door in N-E
      while(sonar.state==0) {
	moto.forwards();
    }
      moto.stop();
      moto.right(2500);
      serv.lookleft();
      wait(1000);
      //IR-logic here while(distance<something), maybe alignment too
      moto.left(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 1) { //door in N-W
      while(sonar.state==0) {
	moto.forwards();
      }
      moto.stop();
      moto.left(2500);
      serv.lookright();
      wait(1000);
      //IR-logic here while(distance<something), maybe alignment too
      moto.right(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 2) { //door in S-E
   moto.right(5000);
      while(sonar.state==0) {
	moto.forwards();
      }
      moto.stop();
      moto.left(2500);
      serv.lookright();
      wait(1000);
      //IR-logic here while(distance<something), maybe alignment too
      moto.right(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 3) { //door in S-W
   moto.right(5000);
      while(sonar.state==0) {
	moto.forwards();
    }
      moto.stop();
      moto.right(2500);
      serv.lookleft();
      wait(1000);
      //IR-logic here while(distance<something) -> moto.forwards() , maybe alignment too
      moto.left(2500);
      moto.forwards(4000);
    }
    if(scan.nearestAnomaly() == 4) { // door hard north, alignment should have put robot far away enough from wall
      serv.lookright();
      wait(1000);
      //IR-logic here while something moto.forwards();
    } 
if(scan.nearestAnomaly() == 5) { // door hard south, alignment should have put robot far away enough from wall
  moto.right(5000);
  serv.lookright();
      wait(1000);
      //IR-logic here while something moto.forwards();
    } 
if(scan.nearestAnomaly() == 6) { // door hard east, alignment should have put robot far away enough from wall
  moto.right(2500);  
  serv.lookright();
      wait(1000);
      //IR-logic here while something moto.forwards();
    } 
if(scan.nearestAnomaly() == 7) { // door hard west, alignment should have put robot far away enough from wall
      serv.lookleft();
      wait(1000);
      //IR-logic here while something moto.forwards();
    } 

  }

  void goHome(){
    if (startingRoom == 0){
	printf("Robot is in room 0 \n");
	currentRoom = 0;

	Robot.moveThroughDoor(0);
	if (baseRoomNumber == 1) {
		Robot.turnRight(90);
		Robot.forwards(6);
		Robot.align("R");
		while (Scan.lookRight() <= 20 && Scan.sonar() >= 30) {
			Robot.forwards();
		}
			Robot.stop();
			Robot.turnRight(90);
			Robot.forwards(4);
			Robot.align("L");
			currentRoom = 1;
			Scan.scan360();
			Map.updateDoors(1, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
			if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
				Robot.goHome();
				return;
			}
		
	}

	if (baseRoomNumber == 2) {
		Robot.turnRight(90);
		while (Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnLeft(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 2;
		Scan.scan360();
		Map.updateDoors(2, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 3) {
		Robot.turnLeft(90);
		Robot.align("R");
		while (Scan.lookRight() <= 20 && Scan.sonar() >= 30){
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 3;
		Scan.scan360();
		Map.updateDoors(3, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

}

if (scan.room() == 1) {
	printf("Robot is in room 1 \n");
	currentRoom = 1;
	Map.updateDoors(1, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
	Robot.moveThroughDoor(1);
	if (baseRoomNumber == 0) {
		Robot.turnLeft(90);
		Robot.align("R");
		Robot.forwards(6);
		While(Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnLeft(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 0;
		Scan.scan360();
		Map.updateDoors(0, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 2) {
		Robot.turnLeft(90);
		Robot.align("R");
		While(Scan.lookRight() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 2;
		Scan.scan360();
		Map.updateDoors(2, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 3) {
		Robot.turnLeft(90);
		Robot.align("R");
		Robot.forwards(6);
		While(Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.align("R");
		while(Scan.lookRight <= 20 && Scan.sonar >= 30){
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 3;
		Scan.scan360();
		Map.updateDoors(3, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}
}


if (scan.room() == 2) {
	printf("Robot is in room 2 \n");
	currentRoom = 2;
	Map.updateDoors(2, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
	Robot.moveThroughDoor(2);
	if (baseRoomNumber == 3) {
		Robot.turnRight(90);
		Robot.forwards(6);
		Robot.align("R");
		while (Scan.lookRight() <= 20 && Scan.sonar() >= 30) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 3;
		Scan.scan360();
		Map.updateDoors(3, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}

	}

	if (baseRoomNumber == 0) {
		Robot.turnRight(90);
		while (Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnLeft(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 0;
		Scan.scan360();
		Map.updateDoors(0, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 1) {
		Robot.turnLeft(90);
		Robot.align("R");
		while (Scan.lookRight() <= 20 && Scan.sonar() >= 30){
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 1;
		Scan.scan360();
		Map.updateDoors(1, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

}

if (scan.room() == 3) {
	printf("Robot is in room 3 \n");
	currentRoom = 3;
	Map.updateDoors(3, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
	Robot.moveThroughDoor(3);
	if (baseRoomNumber == 2) {
		Robot.turnLeft(90);
		Robot.align("R");
		Robot.forwards(6);
		While(Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnLeft(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 2;
		Scan.scan360();
		Map.updateDoors(2, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 0) {
		Robot.turnLeft(90);
		Robot.align("R");
		While(Scan.lookRight() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 0;
		Scan.scan360();
		Map.updateDoors(0, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

	if (baseRoomNumber == 1) {
		Robot.turnLeft(90);
		Robot.align("R");
		Robot.forwards(6);
		While(Scan.lookLeft() <= 20) {
			Robot.forwards();
		}
		Robot.stop();
		Robot.align("R");
		while (Scan.lookRight <= 20 && Scan.sonar >= 30){
			Robot.forwards();
		}
		Robot.stop();
		Robot.turnRight(90);
		Robot.forwards(4);
		Robot.align("L");
		currentRoom = 1;
		Scan.scan360();
		Map.updateDoors(1, Scan.nearestAnomalyX(), Scan.nearestAnomalyY());
		if (Scan.seeBase() == true && currentRoom == baseRoomNumber) {
			Robot.goHome();
			return;
		}
	}

}
  }

};
