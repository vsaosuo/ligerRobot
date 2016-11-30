#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in6,    rightPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in7,    leftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  shaft,          sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  left,           sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  right,          sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port2,           Tright,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           Bright,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightGrab,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftGrab,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Bleft,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Tleft,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

int x;
int rightPotentio;
int leftPotentio;
int y;
void holdArm(){
	motor[Tright] = 15;
	motor[Bright] = 15;
	motor[Bleft] = 15;
	motor[Tleft] = 15;
}

void liftArm(int speed, int degree) {
	if(abs(SensorValue(shaft) - degree) > 1){
		motor[Tright] = (degree-SensorValue[shaft])  * speed / 55;
		motor[Bright] = (degree-SensorValue[shaft])  * speed / 55;
		motor[Bleft] = (degree-SensorValue[shaft])  * speed / 55;
		motor[Tleft] = (degree-SensorValue[shaft])  * speed / 55;
	}
}


void grabAtRange(int range){
	rightPotentio = SensorValue[rightPotentiometer];
	leftPotentio = SensorValue[leftPotentiometer];

	if(rightPotentio > range){
		motor[rightGrab] = abs(rightPotentio - range)/10;
		}else if (rightPotentio < range){
		motor[rightGrab] = abs(rightPotentio - range)/-10;
	}

	if(leftPotentio > range){
		motor[leftGrab] = abs(leftPotentio - range)/10;
		}else if (leftPotentio < range){
		motor[leftGrab] = abs(leftPotentio - range)/-10;
	}
}


void turnLeft(int speed, int degree){ //degree, rotation - 1 or 0 - 1 in clockwise; 0 is counter clockwise

	int encoder = (degree*3.44444444);
	if(nMotorEncoder(right) < encoder){
		motor[rightMotor] = speed;
		motor[leftMotor] = -speed;
		x = nMotorEncoder[leftMotor];
		y = nMotorEncoder[rightMotor];
		}else if (nMotorEncoder(right) > encoder){
		motor[rightMotor] = speed;
		motor[leftMotor] = -speed;
	}
	return;

}

void move(int speed, int distance) {
	int encoder = distance * 12.3309713;

	//while(abs(nMotorEncoder(rightMotor) - distance * 12.3309713) > 10){
	if(nMotorEncoder(rightMotor) < encoder){
		motor[rightMotor] = speed;
		motor[leftMotor] = speed;

		}else if (nMotorEncoder(rightMotor) > encoder){
		motor[rightMotor] = -speed;
		motor[leftMotor] = -speed;
	}
	//}

	return;
}
//*********************************************************************

void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{

		nMotorEncoder[leftMotor] = 0;
		nMotorEncoder[rightMotor] = 0;
		SensorValue[shaft] = 0;
		//****                   Test code               ******************************************


		//*******                End Test code            *******************************************
		while(1 == 2){
			y = nMotorEncoder[rightMotor];
			x = SensorValue[shaft];
		}

		//turn right while opening up the arm
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		while(abs(nMotorEncoder(rightMotor) - (90*3.44444444)) > 10){
			turnLeft(90, 90);
			grabAtRange(900);
		}
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		motor[rightGrab] = 0;
		motor[leftGrab] = 0;
		wait1Msec(300);//correct

		//*********************************************************************

		//move forward
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		while(abs(nMotorEncoder(rightMotor) - 53 * 12.3309713) > 10){
			move(100, 53);

		}
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		wait1Msec(300);//correct

		//*********************************************************************

		//move backward while closing up the claws and lift the arm a bit
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;

		while(abs(nMotorEncoder(rightMotor) + 60 * 12.3309713) > 10){
			move(90, -60);
			grabAtRange(100);
			liftArm(75, 35);
		}
		motor[rightMotor] = 100;
		motor[leftMotor] = 100;
		motor[rightGrab] = 0;
		motor[leftGrab] = 0;
		wait1Msec(200);
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		wait1Msec(300);//correct

		//*********************************************************************

		//turn right
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		while(nMotorEncoder(leftMotor) < 300){
			motor[rightMotor] = (nMotorEncoder(rightMotor) - 260)/2 - 120;
			motor[leftMotor] = 120-(nMotorEncoder(rightMotor) - 260)/2;
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		wait1Msec(300);

		//*********************************************************************

		//move forward while lifting the arm
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		while(abs(nMotorEncoder(rightMotor) - 155 	 * 12.3309713) > 10){
			move(100, 155);
			liftArm(127, 120);
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		holdArm();
		//*********************************************************************

		//open arm
		while(abs(SensorValue[rightPotentiometer] - 900) > 100 || abs(SensorValue[leftPotentiometer] - 900) > 100){
			grabAtRange(900);
		}

		//*********************************************************************

		//*********************************************************************

		while(abs(SensorValue[rightPotentiometer] - 200) > 100 || abs(SensorValue[leftPotentiometer] - 200) > 100){
			grabAtRange(300);
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		motor[rightGrab] = 0;
		motor[leftGrab] = 0;

		//*********************************************************************

		//*********************************************************************

		//move back

		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		wait1Msec(200);
		while(abs(nMotorEncoder(rightMotor) + 23 * 12.3309713) > 10){
			move(90, -23);
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		wait1Msec(300);

		//*********************************************************************

		//open the arm to push

		while(abs(SensorValue[rightPotentiometer] - 1200) > 100 || abs(SensorValue[leftPotentiometer] - 1200) > 100){
			grabAtRange(1800);
		}
		motor[rightGrab] = 0;
		motor[leftGrab] = 0;
		//********************************************************************
		//lower the arm to the stars' level

		motor[Tright] = -20;
		motor[Bright] = -20;
		motor[Bleft] = -20;
		motor[Tleft] = -20;
		wait1Msec(400);

		while(abs(SensorValue[shaft] - 100) > 5){
			liftArm(127, 100);
		}
		holdArm();

		//********************************************************************

		//push forward
		nMotorEncoder[rightMotor] = 0;
		nMotorEncoder[leftMotor] = 0;
		wait1Msec(200);
		while(abs(nMotorEncoder(rightMotor) - 35 * 12.3309713) > 10){
			move(90, 35);
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		wait1Msec(300);

  AutonomousCodePlaceholderForTesting();
}


task usercontrol()
{

  while (true)
  {
    UserControlCodePlaceholderForTesting();
  }
}
