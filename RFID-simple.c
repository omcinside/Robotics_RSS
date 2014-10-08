// - RFID simple -
// This program simply displays the data that is generated by an RFID phidget in a very simple case and outputs it to the console.
// This simple example covers the basics of connecting and using an RFID phidget.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <phidget21.h>

int AttachHandler(CPhidgetHandle RFID, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (RFID, &name);
	CPhidget_getSerialNumber(RFID, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle RFID, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (RFID, &name);
	CPhidget_getSerialNumber(RFID, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle RFID, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s\n", ErrorCode, unknown);
	return 0;
}

int OutputChangeHandler(CPhidgetRFIDHandle RFID, void *usrptr, int Index, int State)
{
	if(Index == 0 || Index == 1)
	{
		printf("Output: %d > State: %d\n", Index, State);
	}
	return 0;
}

int TagHandler(CPhidgetRFIDHandle RFID, void *usrptr, unsigned char *TagVal)
{
	//turn on the Onboard LED
	CPhidgetRFID_setLEDOn(RFID, 1);

	
	printf("Tag Read: %02x%02x%02x%02x%02x\n", TagVal[0], TagVal[1], TagVal[2], TagVal[3], TagVal[4]);
	return 0;
}

int TagLostHandler(CPhidgetRFIDHandle RFID, void *usrptr, unsigned char *TagVal)
{
	//turn off the Onboard LED
	CPhidgetRFID_setLEDOn(RFID, 0);

	printf("Tag Lost: %02x%02x%02x%02x%02x\n", TagVal[0], TagVal[1], TagVal[2], TagVal[3], TagVal[4]);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
//We will also display the nu,mber of available digital outputs
int display_properties(CPhidgetRFIDHandle phid)
{
	int serialNo, version, numOutputs, antennaOn, LEDOn;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetRFID_getOutputCount (phid, &numOutputs);
	CPhidgetRFID_getAntennaOn (phid, &antennaOn);
	CPhidgetRFID_getLEDOn (phid, &LEDOn);


	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Outputs: %d\n\n", numOutputs);
	printf("Antenna Status: %d\nOnboard LED Status: %d\n", antennaOn, LEDOn);

	return 0;
}

int rfid_simple()
{
	int result;
	const char *err;

	//Declare an RFID handle
	CPhidgetRFIDHandle rfid = 0;

	//create the RFID object
	CPhidgetRFID_create(&rfid);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)rfid, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)rfid, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)rfid, ErrorHandler, NULL);

	//Registers a callback that will run if an output changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetRFID_set_OnOutputChange_Handler(rfid, OutputChangeHandler, NULL);

	//Registers a callback that will run when a Tag is read.
	//Requires the handle for the PhidgetRFID, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetRFID_set_OnTag_Handler(rfid, TagHandler, NULL);

	//Registers a callback that will run when a Tag is lost (removed from antenna read range).
	//Requires the handle for the PhidgetRFID, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetRFID_set_OnTagLost_Handler(rfid, TagLostHandler, NULL);

	//open the RFID for device connections
	CPhidget_open((CPhidgetHandle)rfid, -1);

	//get the program to wait for an RFID device to be attached
	printf("Waiting for RFID to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)rfid, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached RFID device
	display_properties(rfid);

	CPhidgetRFID_setAntennaOn(rfid, 1);

	//read RFID event data
	printf("Reading.....\n");

	//keep displaying RFID event data until user input is read
	printf("Press any key to continue\n");
	getchar();

	//toggle the digital output (when making this example I had an LED plugged into the digital output index 0
	CPhidgetRFID_setOutputState(rfid, 0, 1);

	//keep displaying RFID event data until user input is read
	printf("Press any key to continue\n");
	getchar();

	//toggle the digital output (when making this example I had an LED plugged into the digital output index 0
	CPhidgetRFID_setOutputState(rfid, 0, 0);

	printf("Press any key to end\n");
	getchar();

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidget_close((CPhidgetHandle)rfid);
	CPhidget_delete((CPhidgetHandle)rfid);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
	rfid_simple();
	return 0;
}

