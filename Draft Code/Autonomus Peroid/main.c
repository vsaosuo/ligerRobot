#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  armEncoder,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  grabEncoder,    sensorQuadEncoder)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           TrightMotor,   tmotorVex393_MC29, openLoop, reversed)
<<<<<<< HEAD
#pragma config(Motor,  port3,           BrightMotor,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           grabMotor1,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port5,           grabMotor2,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port8,           BleftMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           TleftMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop)
=======
#pragma config(Motor,  port3,           BrightMotor,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           grabMotor1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           grabMotor2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           BleftMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           TleftMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, encoderPort, I2C_2)
>>>>>>> 1cd545a14321f2e0700ff95f50edc23e06277872
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

		//negative == open, positive == close;
		void grab(int speed, int val){
			SensorValue(grabEncoder)= 0;
			while(SensorValue(grabEncoder) == val){
				motor[grabMotor1]= speed;
				motor[grabMotor2]= speed;
			}
			motor[grabMotor1]= 0;
			motor[grabMotor2]= 0;
		}

		void lift(int speed, int time){

			motor[TrightMotor]= speed/2;
			motor[BrightMotor]= speed/2;
			motor[BleftMotor]= speed/2;
			motor[TleftMotor]= speed/2;
			wait1Msec(time);
		}

	//Moving the speed must be less than or = 105
		void move(int speed, int val) {

			resetMotorEncoder(leftMotor);
			resetMotorEncoder(rightMotor);

			while(getMotorEncoder(rightMotor) == val){
			    motor[rightMotor] = speed;
			    motor[leftMotor] = speed;
			}
			 motor[rightMotor] = 0;
 			 motor[leftMotor] = 0;
		}

	//Turning left
		void turnLeft(int speed, int val){
			resetMotorEncoder(leftMotor);
			resetMotorEncoder(rightMotor);
			while(getMotorEncoder(leftMotor) == val){
				motor[leftMotor]= speed * -1;
				motor[rightMotor]= speed;
			}
			motor[leftMotor]= 0;
			motor[rightMotor]= 0;

		}

		//Turning right
		void turnRight(int speed, int val){
			resetMotorEncoder(leftMotor);
			resetMotorEncoder(rightMotor);
			while(getMotorEncoder(rightMotor) == val){
				motor[leftMotor]= speed;
				motor[rightMotor]= speed * -1;
			}
			motor[leftMotor]= 0;
			motor[rightMotor]= 0;
		}

//Finished this at November 11, 2016

task main()
{

	////////////////////////////////////////////////////////////////////////////////
	//                 									First Motion															//
	//	How this motion works?																										//
	//		This motion works, if you put the robot face to the cube, this code 		//
	//	will tells the robot to move to the cube and grab the cube. Then turn to 	//
	//	the fence and drop the cube at other side and stays there to block others.//
	//	Direction:																																//
	// 		. Click the key left of number 7, if your robot is at the left side			//
	//			(if you at the back of the robot).																		//
	//		. Click the key right of number 7, if your robot is at the right side		//
	//			(if you at the back of the robot).																		//
	////////////////////////////////////////////////////////////////////////////////
	if(vexRT(Btn7L) == 1){

		move(105, 2010); // Move forward
		grab(110, 250); // hole on to the cube, 279.287587mm 28 cm
		turnLeft(110, 35); // turn left if our robot is at the left side
		move(105, 2010); // move forward untile near the middle fence
		lift(100, 1500); // lift the cube up
		move(60, 5); // move a bit
		grab(-110, 200); // drop the cube
		// stay there to block
	}
	else if (vexRT(Btn7R) == 1){

		move(105, 2010); // Move forward
		grab(110, 250); // hole on to the cube, 279.287587mm 28 cm
		turnRight(110, 35); // turn right if our robot is at the left side
		move(105, 2010); // move forward untile near the middle fence
		lift(100, 1500); // lift the cube up
		move(60, 5); // move a bit
		grab(-110, 200); // drop the cube
		// stay there to block
	}
	else{
		motor[rightMotor]=0; //do nothing
		motor[leftMotor]=0; //do nothhing
	}
}
