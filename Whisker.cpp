#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std; 

class Whisker {

private:

  int inputsignal;
  double timer; //counts how long it has been since last time in() has been called
	

public:

   Whisker() { //default constructor
		inputsignal = 0;
		timer = clock();

   }

  void in(int signal) {
		inputsignal=signal;

		//reset timedifference
		timer = clock();
	}

  int state() {
		//whisker.in hasn't been called in over a second  -> steady state
		if ((clock()-timer)/CLOCKS_PER_SEC>0.1) {
			return inputsignal;
		}

		else{ //whisker.in is being called constantly
			return 2; //must be vibrating
		}

	}




};

