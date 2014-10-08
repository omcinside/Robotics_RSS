// - Servo simple -
// This simple example sets up a Servo objectm hooks the event handlers and opens it for device connections.  Once a Servo is attached
// with a motor in motor 0 it will simulate moving the motor from position 15 to 231, displaying the event details to the console.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <phidget21.h>

int AttachHandler(CPhidgetHandle SERV, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (SERV, &name);
	CPhidget_getSerialNumber(SERV, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle SERV, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (SERV, &name);
	CPhidget_getSerialNumber(SERV, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle SERV, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

int PositionChangeHandler(CPhidgetServoHandle SERV, void *usrptr, int Index, double Value)
{
	printf("Motor: %d > Current Position: %f\n", Index, Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetServoHandle phid)
{
	int serialNo, version, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetServo_getMotorCount (phid, &numMotors);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

	return 0;
}

class Servo {

public:

	CPhidgetServoHandle ServoContrl;
	int state;     //Is state of serve needed? Probably not. 

	Servo (){
		int result;
		const char *err;
		double curr_pos;

		ServoContrl = 0;
		state = 0;
		
		//Declare a servo handle
		CPhidgetServoHandle servo = 0;

		//create the servo object
		CPhidgetServo_create(&servo);
	
		//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
		CPhidget_set_OnAttach_Handler((CPhidgetHandle)servo, AttachHandler, NULL);
		CPhidget_set_OnDetach_Handler((CPhidgetHandle)servo, DetachHandler, NULL);
		CPhidget_set_OnError_Handler((CPhidgetHandle)servo, ErrorHandler, NULL);

		//Registers a callback that will run when the motor position is changed.
		//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetServo_set_OnPositionChange_Handler(servo, PositionChangeHandler, NULL);

		//open the servo for device connections
		CPhidget_open((CPhidgetHandle)servo, -1);

		//get the program to wait for an servo device to be attached
		printf("Waiting for Servo controller to be attached....");
		if((result = CPhidget_waitForAttachment((CPhidgetHandle)servo, 10000)))
		{
			CPhidget_getErrorDescription(result, &err);
			printf("Problem waiting for attachment: %s\n", err);
			return 0;
		}

		//display_properties(servo);

		//display current motor position
		CPhidgetServo_getPosition(servo, 0, &curr_pos);
		printf("Motor: 0 > Current Position: %f\n", curr_pos);

		//valid range is -22 to 232.....this gives us 255 positions so
		//-22 is either extreme right or left.
		//We will need to workout the value of what's straight ahead with out Snailbot


	void lookleft()
	{
			//Set position extreme left
			state = -22;
			CPhidgetServo_setPosition (servo, 0, -22); //could be revsersed as I'm unsure of the servo orientation
	}

	void lookright()
	{
		//Set position extreme right
		state = 232;
		CPhidgetServo_setPosition (servo, 0, direction); //or 232
	}

	//This may have to call upon IR sensor scan and maybe return anomolies found and their distance/orientation
	int 180DegreeScan()
	{
			//Set position extreme left
			CPhidgetServo_setPosition (servo, 0, -22); //could be revsersed as I'm unsure of the servo orientation
			//while (curr_pos != -22){} //waits for servo to set position to max left. 
			for (int i =-22; i < 232; i++){
				CPhidgetServo_setPosition (servo, 0, i);
				//run IR scan logic to look for obstacles
			}
	}

	void disconnect()
	{
		//By default always set servo back to facing foward
		CPhidgetServo_setPosition (servo, 116, direction);
		//disengage servo to save battery power
		CPhidgetServo_setEngaged (servo, 0, 0);
		CPhidget_close((CPhidgetHandle)servo);
		CPhidget_delete((CPhidgetHandle)servo);
	}

	int DirectionState()
	{
	return state;
	}
};
