


//robot is placed in starting position at (0,0)
//do a 360 degree scan
Scan.scan360();

//First: check if we are already next to the base
if (Scan.seeBase()== true) {
	Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
	Robot.goHome(); //uses the base location on the map to go home
	Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
	return;
}


//otherwise we are in some room in the base, but we do not know which:
/*
|---------------------|
|     2    |     1    |
|          |          |
|   -------    -------|
|			3		  |
|--------   -------   |
|	 1		|	2	  |		
|			|         |
|---------------------|

base is symmetric, doesn't matter which corner we're in, need to find out if we're in 1,2 or 3 -> once determined the opposite 1 and 2 become 4 and 5 */

//if this is the case must be in either room 1 or 2
if (Scan.numberOfAnomalies() == 1) {
	printf("1 anomaly found, we are in room 1 or 2 \n");
	Map.updateDoors(0); //uses the anomaly data to put a door on the map, gives it label 0
	Robot.moveThroughDoor(0); //robot moves through door 0 by first aligning with a wall at right angles 
	//have the robot look right after it's moved through the door, if there is a wall there, we have started in room 0
	if (Scan.lookRight() <= 20) { 
		printf("Robot starting position was in room 2 \n");
		Map.associateRoom(2, 0); //associate door 0 to room 2
		//move towards center
		Robot.turnLeft(90); //turn 90 degrees to the left
		Robot.align("R"); //aligns the robot with the right wall at 90 degrees

		while (Scan.lookRight() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}

		//the base might be somewhere in the corridor (i.e. room 3)
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}

		Robot.turnRight(90);
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 1
		printf("Robot entering room 1 \n");
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(1); //uses the anomaly data to put a door on the map, gives it label 1
			Map.associateRoom(1, 1);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}
		printf("Base is not in room 1. \n");

		Robot.reverse(2); //go back to the center of the map
		Robot.turnLeft(90);
		Robot.align("L");
		while (Scan.lookLeft() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}
		Robot.turnLeft(90);
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 4
		printf("Robot entering room 4. \n");
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(2); //uses the anomaly data to put a door on the map, gives it label 2
			Map.associateRoom(4, 2);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}
		printf("Base is not in room 4. \n");

		Robot.reverse(2); //go back to the center of the map
		Robot.turnRight(90);
		Robot.align("R");
		while (Scan.lookRight() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}
		Robot.turnRight(90);
		printf("Entering room 5. \n");
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 5
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(3); //uses the anomaly data to put a door on the map, gives it label 3
			Map.associateRoom(5, 3);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}

		//we have gone through the map and not found anything
		printf("Robot has been unable to find base, started in room 2. \n");
		return;
	}


	// if we didn't start in room 2 and the total number of anomalies is 1 from our scan, then we started in room 1
	else {
		printf("Robot starting position was in room 1 \n");
		Map.associateRoom(1, 0);

		//the base might be somewhere in the corridor (i.e. room 3)
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}

		//move towards room 2
		Robot.turnLeft(90); //turn 90 degrees to the left
		Robot.align("R"); //aligns the robot with the right wall at 90 degrees

		while (Scan.lookRight() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}
		Robot.turnRight(90);
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 1
		printf("Robot entering room 2 \n");
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(1); //uses the anomaly data to put a door on the map, gives it label 1
			Map.associateRoom(2, 1);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}
		printf("Base is not in room 2. \n");

		Robot.reverse(2); //go back to the center of the map
		Robot.turnRight(90);
		Robot.align("R");
		Robot.forwards(2);
		Robot.align("L");
		while (Scan.lookLeft() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}
		Robot.turnLeft(90);
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 4
		printf("Robot entering room 4. \n");
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(2); //uses the anomaly data to put a door on the map, gives it label 2
			Map.associateRoom(4, 2);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}
		printf("Base is not in room 4. \n");

		Robot.reverse(2); //go back to the center of the map
		Robot.turnRight(90);
		Robot.align("R");
		while (Scan.lookRight() <= 20){
			Robot.forwards();
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		}
		Robot.turnRight(90);
		printf("Entering room 5. \n");
		Robot.forwards(2); //go forwards 2 seconds, we are entering room 5
		Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
		Robot.align("L");
		Scan.scan360();
		if (Scan.seeBase() == true) {
			Map.setBase(scan.getBaseLocation()); //sets the location of the base in x,y coordinates w.r.t. the origin which is the robots original starting position
			Map.updateDoors(3); //uses the anomaly data to put a door on the map, gives it label 3
			Map.associateRoom(5, 3);
			Robot.goHome(); //uses the base location on the map to go home
			Robot.updatePosition(); //update the position of the robot on the map using its current orientation and the distance it's moved
			return;
		}

		//we have gone through the map and not found anything
		printf("Robot has been unable to find base, started in room 1. \n");
		return;
	}
}

//if the number of anomalies> 1 then we must have started in the middle bit, room 3
if (Scan.numberofAnomalies() > 1) {
	printf("multiple anomalies found, we are in room 3 \n");
	Map.updateDoors(0); //uses the anomaly data to put anomalies on the map, gives it label 0
	Robot.moveThroughDoor(0); //robot moves through door 0 by first aligning with a wall at right angles 

	//-> now we are in room 1 or 2 again and we can follow the logic from before
}

if (Scan.numberofAnomalies() == 0) {
	Robot.move(10); //if the robot can't find any anomalies for whatever reason move randomly for a while before checking again
	Scan.scan360();
	//-> repeat above logic
}