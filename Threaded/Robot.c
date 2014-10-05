#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <phidget21.h>
#include <pthread.h>
#include <libpowerbutton.h>
#include "Sensors.h"
#include "Moto.h"

int main(int argc, char* argv[])
{
	pthread_t senth, mapth, camth;
	int id1 = 1;
	int id2 = 2;
	int id3 = 3;
	pthread_create(&soth, NULL, sensorThread, (void*)&id1);	pthread_create(&mapth, NULL, mapThread, (void*)&id2);
	pthread_create(&camth, NULL, cameraThread, (void*)&id3);


	getChar();
	camRun = false;
	sensorRun = false;
	mapRun = false;

	wait(2000);
	return 0;
}
