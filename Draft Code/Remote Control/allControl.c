#pragma config(Sensor, in1,    armPotentiometer, sensorPotentiometer)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           topRightMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           bottomRightMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightGrapMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftGrapMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           bottomLeftMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           topLeftMotor,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int x;
task main()
{
	while(1==1){
		x = SensorValue[armPotentiometer];
		motor[rightMotor] = vexRT[Ch2]; //move RIGHT motor by CH2
		motor[leftMotor] = vexRT[Ch3]; //move LEFT motor by CH3

		if(vexRT[Btn6U] == 1) //if Btn6U is click the arm rise up
		{
			motor[topRightMotor] = 65;
			motor[bottomRightMotor] = 65;
			motor[topLeftMotor] = 65;
			motor[bottomLeftMotor] = 65;
		}
		else if(vexRT[Btn6D] == 1) //if Btn6D is click the arm fall down in a low speed
		{
			motor[topRightMotor] = -10;
			motor[bottomRightMotor] = -10;
			motor[topLeftMotor] = -10;
			motor[bottomLeftMotor] = -10;
		}
		else //The motor still moving in a 15 speed to stop the arm in the mid air.
		{
			motor[topRightMotor] = 15;
			motor[bottomRightMotor] = 15;
			motor[topLeftMotor] = 15;
			motor[bottomLeftMotor] = 15;
		}
		if(vexRT[Btn5U] == 1)
		{
			motor[rightGrapMotor] = 100;
			motor[leftGrapMotor] = 100;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[rightGrapMotor] = -100;
			motor[leftGrapMotor] = -100;
		}
		else
		{
			motor[rightGrapMotor] = 0;
			motor[leftGrapMotor] = 0;
		}

		if(vexRT[Btn8U] == 1){
			while(SensorValue[armPotentiometer] < 2700) //If the Potentiometer
			{ //has not reached its maximum point...
				motor[topRightMotor] = 65;
				motor[bottomRightMotor] = 65;
				motor[topLeftMotor] = 65;
				motor[bottomLeftMotor] = 65;

				motor[rightMotor] = vexRT[Ch2]; //move RIGHT motor by CH2
				motor[leftMotor] = vexRT[Ch3]; //move LEFT motor by CH3

				if(vexRT[Btn8D] == 1) {
					break;
				}
			}
		}

		if(vexRT[Btn8D] == 1) {
			while(SensorValue[armPotentiometer] > 1250) //If the Potentiometer
			{
				motor[topRightMotor] = -10 ;
				motor[bottomRightMotor] = -10;
				motor[topLeftMotor] = -10;
				motor[bottomLeftMotor] = -10;

				motor[rightMotor] = vexRT[Ch2]; //move RIGHT motor by CH2
				motor[leftMotor] = vexRT[Ch3]; //move LEFT motor by CH3
				if(vexRT[Btn8U] == 1) {
					break;
				}
			}
		}
	}
}
