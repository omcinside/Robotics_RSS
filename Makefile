default:
	g++ Accelerometer-simple.c -o Accelerometer-simple -lphidget21 
	g++ AdvancedServo-simple.c -o AdvancedServo-simple -lphidget21
	g++ Analog-simple.c -o Analog-simple -lphidget21
	g++ Bridge-simple.c -o Bridge-simple -lphidget21
	g++ Dictionary-simple.c -o Dictionary-simple -lphidget21
	g++ Encoder-simple.c -o Encoder-simple -lphidget21
	g++ FrequencyCounter-simple.c -o FrequencyCounter-simple -lphidget21
	g++ GPS-simple.c -o GPS-simple 	-lphidget21
	g++ InterfaceKit-simple.c -o InterfaceKit-simple -lphidget21
	g++ IR-simple.c -o IR-simple -lphidget21
	g++ LED-simple.c -o LED-simple -lphidget21
	g++ Manager-simple.c -o Manager-simple -lphidget21
	g++ MotorControl-simple.c -o MotorControl-simple -lphidget21
	g++ PHSensor-simple.c -o PHSensor-simple -lphidget21
	g++ RFID-simple.c -o RFID-simple -lphidget21
	g++ Servo-simple.c -o Servo-simple -lphidget21
	g++ Spatial-simple.c -o Spatial-simple -lphidget21
	g++ Stepper-simple.c -o Stepper-simple -lphidget21
	g++ TemperatureSensor-simple.c -o TemperatureSensor-simple -lphidget21
	g++ TextLCD-simple.c -o TextLCD-simple -lphidget21
	g++ power_button.cpp -o power_button -lpowerbutton
	g++ helloworldcv.cpp -o helloworldcv `pkg-config opencv --cflags --libs`
