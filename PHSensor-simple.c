// - PHSensor simple -
// This simple example simply opens a PH sensor phidget and waits for one to be attached.  The program will then wait for
// user input to terminate.  While waiting it will display the data generated by the events, such as the PH change event
// which will display the currently measured PH without sensitivity modifications.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <phidget21.h>

int AttachHandler(CPhidgetHandle PH, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (PH, &name);
	CPhidget_getSerialNumber(PH, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle PH, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (PH, &name);
	CPhidget_getSerialNumber(PH, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle PH, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

int PHChangeHandler(CPhidgetPHSensorHandle PH, void *usrptr, double Value)
{
	double potential;
	CPhidgetPHSensor_getPotential(PH, &potential);

	printf("PH: %f -- Potential: %f\n", Value, potential);
	return 0;
}
//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetPHSensorHandle phid)
{
	int serialNo, version;
	double trigger, potential;
	double min, max;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetPHSensor_getPHChangeTrigger(phid, &trigger);
	CPhidgetPHSensor_getPotential(phid, &potential);


	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("Trigger Sensitivity: %f\nPotential: %f\n", trigger, potential);
	CPhidgetPHSensor_getPHMax(phid, &max);
	CPhidgetPHSensor_getPHMin(phid, &min);
	printf("Max PH: %0.4lf, Min PH: %0.4lf\n", max, min);
	CPhidgetPHSensor_getPotentialMax(phid, &max);
	CPhidgetPHSensor_getPotentialMin(phid, &min);
	printf("Max Potential: %0.2lfmV, Min Potential: %0.2lfmV\n", max, min);

	return 0;
}

int ph_simple()
{
	int result;
	const char *err;

	//Declare an PH Sensor handle
	CPhidgetPHSensorHandle ph = 0;

	//create the PH Sensor object
	CPhidgetPHSensor_create(&ph);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)ph, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)ph, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)ph, ErrorHandler, NULL);

	//Registers a callback that will run if the PH changes by more than the PH trigger.
	//Requires the handle for the PHSensor, the function that will be called, and a arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetPHSensor_set_OnPHChange_Handler(ph, PHChangeHandler, NULL);

	//open the PH Sensor for device connections
	CPhidget_open((CPhidgetHandle)ph, -1);

	//get the program to wait for an PH Sensor device to be attached
	printf("Waiting for PH Sensor to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)ph, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached PH Sensor device
	display_properties(ph);

	//read PH Sensor event data
	printf("Reading.....\n");

	//increase the sensitivity
	printf("Increasing sensitivity to 0.01, Press any key to continue\n");
	getchar();

	CPhidgetPHSensor_setPHChangeTrigger (ph, 0.01);

	//change temp
	printf("Changing Temp to 50 degrees\n");
	getchar();

	CPhidgetPHSensor_setTemperature (ph, 50);
	display_properties(ph);

	//end
	printf("Press any key to end\n");
	getchar();

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)ph);
	CPhidget_delete((CPhidgetHandle)ph);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
	ph_simple();
	return 0;
}
