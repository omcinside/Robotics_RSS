
class Robot {

private: 


public:

	Robot() { //default constructor


	}

	void moveToTarget(double x, double y) {

		// some logic to move to a target in an organised manner i.e. certain amounts of x and y
		// include obstacle avoidance
	}

	void goHome() {
		moveToTarget(Map.getBaseX(), Map.getBaseY());
	}

	void moveThroughDoor(int label) {
		moveToTarget(Map.getDoorX(label), Map.getDoorY(label));
		forwards(1); //move the robot forwards for 1 second to go through the door
	}

	void turnLeft() {

	}

	void forwards() {

	}

	void forwards(int seconds) {
		//move forwards for x amount of seconds
	}

	void backwards() {

	}

	void backwards(int seconds) {

	}

	void stop() {

	}

	void turnRight() {

	}

	void turnLeft(int degrees) {
		
		while ( /*need some calibration stuff here*/) {
			turnLeft();
		}
	}

	void turnRight(int degrees) {

		while ( /*need some calibration stuff here*/) {
			turnRight();
		}

	}

	void align(int direction) { //e.g. use 0 for right, 1 for left
		//logic for aligning here, use IR
	}

};
