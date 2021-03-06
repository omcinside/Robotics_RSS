#include <stdio>
#include "Scan.h"





//robot is placed in starting position at (0,0) COULD MAKE SENSE TO ALIGN WITH WALL FIRST SO THAT AXES OF FRAME OF REFERENCE ARE NICE WRT ARENA
//do a 360 degree scan
Scan.scan360();

Map.setBase(baseRoomNumber);

//First: check if we are already next to the base
if (Scan.seeBase()== true) {
	
	Robot.goHome(); //uses the base location on the map to go home
	Map.updatePosition(Robot.deltax(),Robot.deltaY()); //update the position of the robot on the map using its current orientation and the distance it's moved
	return;
}


//otherwise we are in some room in the base, but we do not know which:
/*
|---------------------|
|     3    |     2    |
|          |          |
|   -------    -------|
|			5		  |
|--------   -------   |
|	 0		|	1	  |		
|			|         |
|---------------------|

base is symmetric, doesn't matter which corner we're in, need to find out if we're in 0,1 or 5 -> once determined the opposite 0 and 1 become 2 and 3 */


if (scan.room() == 0){
	printf("Robot is in room 0 \n");
	currentRoom = 0;
	Map.updateDoors(0, Scan.nearestAnomalyX(), Scan.nearestAnomalyY()); //door 0 signifies room 0
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

//if the number of anomalies> 1 then we must have started in the middle bit, room 3
if (Scan.numberofAnomalies() > 1) {
	printf("multiple anomalies found, we are in room 3 \n");
	Map.updateDoors(0); //uses the anomaly data to put anomalies on the map, gives it label 0
	Robot.moveThroughDoor(0); //robot moves through door 0 by first aligning with a wall at right angles 
	Map.updatePosition(Robot.deltax(), Robot.deltaY());
	//-> now we are in room 1 or 2 again and we can follow the logic from before
}

if (Scan.numberofAnomalies() == 0) {
	Robot.move(10); //if the robot can't find any anomalies for whatever reason move randomly for a while before checking again
	Scan.scan360();
	//-> repeat above logic
}
