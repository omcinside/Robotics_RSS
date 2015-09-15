#include <phidget21.h>
#include <pthread.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <libpowerbutton.h>
#include "Moto.h"
#include "servo.h"
#include "IR.h"
#include "Scan.h"
#include "Whisker.h"
#include "HallE.h"
#include "Sonar.h"
#include "wait.h"


int main(int argc, char* argv[])
{
	Moto moto;
	IR ir;
	Servo servo;
	scan.scan180();
	printf ("Aligning to Left Wall");
	moto.AlignLeftWall();
	printf ("Successfully Aligned to Left Wall....Moving foward 5 seconds");
	return 0;
};

