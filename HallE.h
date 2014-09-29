#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std; 

class HallE {

 private:

  int inputsignal;
  time_t timer,end;
 
	

 public:

  HallE() { //default constructor
    inputsignal = 0;
    time(&timer); 
  }

  void in(int signal) {
    //printf("Hall signal: %d\n",signal);
    inputsignal=signal;
	

    //reset timedifference
    time(&timer);
    //printf("timer1: %d \n", timer);
  }

  int state() {
    
    //whisker.in hasn't been called in over a second  -> steady state
    if ((time(&end)-timer)>=5) {	  
      //printf("timer:%d , clock: %d , difference:%d \n ",timer,time(&end), time(&end)-timer);
      return 1;
			
  }

  else{ //whisker.in is being called constantly
    return 0; //must be vibrating
  }

}




};

