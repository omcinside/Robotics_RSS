// - MotorControl simple -
// This simple example creates a MotorControl handle, hooks the event handlers, then opens and waits for a MotorControl Phidget to be attached.
// Once on has been attaced it will display device information and display any event data read.  The program will then do a short simulation
// of the functionality of the motor by increasing and decreasing the speed of an attached motor.  PLEASE NOTE:  This assignment
// was desgined assuming only one motor attached at motor index 0 (for motorcontrol boards with multiple motors).
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <phidget21.h>

int AttachHandler(CPhidgetHandle MC, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (MC, &name);
	CPhidget_getSerialNumber(MC, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle MC, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (MC, &name);
	CPhidget_getSerialNumber(MC, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle MC, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}


int InputChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, int State)
{
	printf("Input %d > State: %d\n", Index, State);
	return 0;
}

int VelocityChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	printf("Motor %d > Current Speed: %f\n", Index, Value);
	return 0;
}

int CurrentChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	printf("Motor: %d > Current Draw: %f\n", Index, Value);
	return 0;
}

int display_properties(CPhidgetMotorControlHandle phid)
{
	int serialNo, version, numInputs, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);
	
	CPhidgetMotorControl_getInputCount(phid, &numInputs);
	CPhidgetMotorControl_getMotorCount(phid, &numMotors);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Inputs: %d\n# Motors: %d\n", numInputs, numMotors);

	return 0;
}

int forwards()
{
	int result;
	const char *err;

	//Declare a motor control handle
	CPhidgetMotorControlHandle motoControl = 0;
	//CPhidgetMotorControlHandle motoControl2 = 1;

	//create the motor control object
	CPhidgetMotorControl_create(&motoControl);
	//CPhidgetMotorControl_create(&motoControl2);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)motoControl, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)motoControl, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)motoControl, ErrorHandler, NULL);
	/*	CPhidget_set_OnAttach_Handler((CPhidgetHandle)motoControl2, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)motoControl2, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)motoControl2, ErrorHandler, NULL);*/

	//Registers a callback that will run if an input changes.
	//Requires the handle for the Phidget, the function that will be called, and a arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetMotorControl_set_OnInputChange_Handler (motoControl, InputChangeHandler, NULL);
	//CPhidgetMotorControl_set_OnInputChange_Handler (motoControl2, InputChangeHandler, NULL);

	//Registers a callback that will run if a motor changes.
	//Requires the handle for the Phidget, the function that will be called, and a arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetMotorControl_set_OnVelocityChange_Handler (motoControl, VelocityChangeHandler, NULL);
	//CPhidgetMotorControl_set_OnVelocityChange_Handler (motoControl2, VelocityChangeHandler, NULL);

	//Registers a callback that will run if the current draw changes.
	//Requires the handle for the Phidget, the function that will be called, and a arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetMotorControl_set_OnCurrentChange_Handler (motoControl, CurrentChangeHandler, NULL);
	//CPhidgetMotorControl_set_OnCurrentChange_Handler (motoControl2, CurrentChangeHandler, NULL);

	//open the motor control for device connections
	CPhidget_open((CPhidgetHandle)motoControl, -1);
	//CPhidget_open((CPhidgetHandle)motoControl2, -1);

	//get the program to wait for a motor control device to be attached
	printf("Waiting for MotorControl to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)motoControl, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}
	/*if((result = CPhidget_waitForAttachment((CPhidgetHandle)motoControl2, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment 2: %s\n", err);
		return 0;
		}*/

	//Display the properties of the attached motor control device
	display_properties(motoControl);
	//display_properties(motoControl2);

	//read motor control event data
	printf("Reading.....\n");

	//keep displaying motor control event data until user input is read
	printf("Press any key to continue\n");
	getchar();

	//Control the motor a bit.
	//Step 1: increase acceleration to 50, set target sped at 100
	/*CPhidgetMotorControl_setAcceleration (motoControl, 0, -50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 0, -100.00);
	CPhidgetMotorControl_setAcceleration (motoControl, 1, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 1, 100.00);

	printf("Press any key to continue\n");
	getchar();*/

	//Step 2: Set acceleration to 100, decrease target speed to 75
	CPhidgetMotorControl_setAcceleration (motoControl, 0, -100.00);
	CPhidgetMotorControl_setVelocity (motoControl, 0, -100.00);
	CPhidgetMotorControl_setAcceleration (motoControl, 1, 100.00);
	CPhidgetMotorControl_setVelocity (motoControl, 1, 70.00);

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)motoControl);
	CPhidget_delete((CPhidgetHandle)motoControl);
	/*CPhidget_close((CPhidgetHandle)motoControl2);
	  CPhidget_delete((CPhidgetHandle)motoControl2);*/

	//all done, exit
	return 0;
}

