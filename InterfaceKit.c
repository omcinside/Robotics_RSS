// - InterfaceKit simple -
// This simple example simply creates an InterfaceKit handle, hooks the event handlers and opens it.  It then waits
// for an InterfaceKit to be attached and waits for events to be fired. We progress through three steps, 1. Normal settings, 
// 2. Setting analog sensor sensitivity to 100, 3. Toggling Ratiometric, waiting for user input to proceed to next step to allow 
// data to be read.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <phidget21.h>
//#include <list>
#include <pthread.h>
#include <libpowerbutton.h>
#include "Whisker.h"
#include "HallE.h"
#include "Moto.h"
#include "Sonar.h"

Sonar sonar;
HallE hall;
Moto motor;

Whisker whleft;
Whisker whright;

int AttachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName(IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s", ErrorCode, unknown);
	return 0;
}

//callback that will run if an input changes.
//Index - Index of the input that generated the event, State - boolean (0 or 1) representing the input state (on or off)
int InputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{
  if (Index == 4)
    {
      whleft.in(State);
    }
  else if(Index == 5)
    {
      whright.in(State);
    }
  else if(Index == 7)
    {
      hall.in(State);
    }
  //printf("Digital Input: %d > State: %d\n", Index, State);
  //printf("Hall: %d \n",hall.state());
	return 0;
}

//callback that will run if an output changes.
//Index - Index of the output that generated the event, State - boolean (0 or 1) representing the output state (on or off)
int OutputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{
	printf("Digital Output: %d > State: %d\n", Index, State);
	return 0;
}

//callback that will run if the sensor value changes by more than the OnSensorChange trigger.
//Index - Index of the sensor that generated the event, Value - the sensor read value
int SensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
  if(Index == 1)
    {
      sonar.in(Value);
      }
  //printf("Sensor: %d > Value: %d\n", Index, Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
//Will also display the number of inputs, outputs, and analog inputs on the interface kit as well as the state of the ratiometric flag
//and the current analog sensor sensitivity.
int display_properties(CPhidgetInterfaceKitHandle phid)
{
	int serialNo, version, numInputs, numOutputs, numSensors, triggerVal, ratiometric, i;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetInterfaceKit_getInputCount(phid, &numInputs);
	CPhidgetInterfaceKit_getOutputCount(phid, &numOutputs);
	CPhidgetInterfaceKit_getSensorCount(phid, &numSensors);
	CPhidgetInterfaceKit_getRatiometric(phid, &ratiometric);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Digital Inputs: %d\n# Digital Outputs: %d\n", numInputs, numOutputs);
	printf("# Sensors: %d\n", numSensors);
	printf("Ratiometric: %d\n", ratiometric);

	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_getSensorChangeTrigger (phid, i, &triggerVal);

		printf("Sensor#: %d > Sensitivity Trigger: %d\n", i, triggerVal);
	}

	return 0;
}


int interfacekit_simple()
{
	int result, numSensors, i;
	const char *err;

	//Declare an InterfaceKit handle
	CPhidgetInterfaceKitHandle ifKit = 0;

	//create the InterfaceKit object
	CPhidgetInterfaceKit_create(&ifKit);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)ifKit, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)ifKit, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)ifKit, ErrorHandler, NULL);

	//Registers a callback that will run if an input changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnInputChange_Handler (ifKit, InputChangeHandler, NULL);

	//Registers a callback that will run if the sensor value changes by more than the OnSensorChange trig-ger.
	//Requires the handle for the IntefaceKit, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnSensorChange_Handler (ifKit, SensorChangeHandler, NULL);

	//Registers a callback that will run if an output changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnOutputChange_Handler (ifKit, OutputChangeHandler, NULL);

	//open the interfacekit for device connections
	CPhidget_open((CPhidgetHandle)ifKit, -1);

	//get the program to wait for an interface kit device to be attached
	printf("Waiting for interface kit to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)ifKit, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	int count = 0;
	bool run = true;
	power_button_reset();
	while (run)
	  {
	    printf("Hello\n");
	    int lw = whleft.state();
	    int rw = whright.state();
	    int he = hall.state();
	    int sn = sonar.state();
	    if(power_button_get_value() >= 2){
	      power_button_reset();
	    }
	    if(he == 1 && motor.moveState() == 1){
	      count +=1;
	    }
	    if(he == 0){
	      count = 0;
	    }
	    if(power_button_get_value() < 1){
	      motor.stop();
	      count = 0;
	    }else if (sn == 1) {
	      motor.right();
	    }else if(lw == 1) {
	      motor.right();
	    }else if(rw == 1) {
	      motor.left();
	    }else if(he == 1 && motor.moveState() == 1 && count>5) {
	       motor.reverse();
	       sleep(5);
	       motor.right();
	       sleep(3);
	       count =0;
	    }else{
	      motor.forwards();
	    }

	    printf("Left Whisker: %d, Right Whisker: %d, Hall Effect: %d, Sonar: %d\n", lw, rw, he, sn);
	    sleep(1);

	    
	  }

	//Display the properties of the attached interface kit device
	display_properties(ifKit);

	//read interface kit event data
	/*printf("Reading.....\n");

	//keep displaying interface kit data until user input is read
	printf("Press any key to go to next step\n");
	getchar();

	printf("Modifying sensor sensitivity triggers....\n");

	//get the number of sensors available
	CPhidgetInterfaceKit_getSensorCount(ifKit, &numSensors);

	//Change the sensitivity trigger of the sensors
	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, i, 100);  //we'll just use 10 for fun
	}

	//read interface kit event data
	printf("Reading.....\n");

	//keep displaying interface kit data until user input is read
	printf("Press any key to go to next step\n");
	getchar();

	printf("Toggling Ratiometric....\n");

	CPhidgetInterfaceKit_setRatiometric(ifKit, 0);

	//read interface kit event data
	printf("Reading.....\n");*/

	//keep displaying interface kit data until user input is read
	printf("Press any key to end\n");
	getchar();

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)ifKit);
	CPhidget_delete((CPhidgetHandle)ifKit);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
  //Whisker left();
  //Whisker right();
	interfacekit_simple();
	return 0;
}

