#pragma config(Sensor, in1,    potentiometerScissorsLeft, sensorPotentiometer)
#pragma config(Sensor, in2,    potentiometerScissorsRight, sensorNone)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mobileGoalLift, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           scissorsRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           scissorsLeft,  tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int threshold = 15; // torelance between each joystick
int limitRPM = 160; // For high torque motor the has a limit speed
int sisSpeed = 127; // For scissors speed
/*
void sciEqual(){
	int maxSpeed = 117;
	int potThreshold = 30;
	int maxDiff = 150;

	int err = abs(SensorValue[scissorsRight] - SensorValue[scissorsLeft]);
	if(){
	}
}*/

task main()
{
	while(true){
		int y = vexRT[Ch2];
		int x = vexRT[Ch1];
		int r = vexRT[Ch4];


   if(abs(y) > threshold && abs(y) < limitRPM)	y = vexRT[Ch2];
   else	y = 0;

   if(abs(x) > threshold && abs(x) < limitRPM)	x = vexRT[Ch1];
   else	x = 0;

   if(abs(r) > threshold)	r = vexRT[Ch4]/2;
   else	r = 0;

		// Y component, X component, Rotation
		motor[frontLeft] =   y + x + r;
		motor[frontRight] =  -y + x + r;
		motor[backRight] =  -y - x + r;
		motor[backLeft] =   y - x + r;

		// Arm Control
    if(vexRT[Btn6U] == 1){
      motor[mobileGoalLift] = 90;
    } else if(vexRT[Btn6D] == 1){
      motor[mobileGoalLift] = -90;
    } else{
      motor[mobileGoalLift] = 0;
    }

    // Scissors Lift
    if(vexRT[Btn5U] == 1){
      motor[scissorsLeft] = sisSpeed;
      motor[scissorsRight] = sisSpeed;
    } else if(vexRT[Btn5D] == 1){
      motor[scissorsLeft] = -sisSpeed;
      motor[scissorsRight] = -sisSpeed;
    } else{
      motor[scissorsLeft] = 0;
      motor[scissorsRight] = 0;
    }

    // Motor values can only be updated every 20ms
		wait10Msec(2);
	}
}