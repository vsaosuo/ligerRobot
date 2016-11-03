#pragma config(Sensor, in1,    potentiometerArm, sensorPotentiometer)
#pragma config(Sensor, in3,    potentiometerGrab, sensorPotentiometer)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port5,           grabMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           armMotorL,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           armMotorR,     tmotorNone, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void resetArm(){
	if(SensorValue(potentiometerArm) >= 5){
		motor[armMotorL]= -100;
		motor[armMotorR]= -100;
		waitUntil(SensorValue(potentiometerArm) < 5);
		stopMotor(armMotorL);
		stopMotor(armMotorR);
	}else{
		stopMotor(armMotorL);
		stopMotor(armMotorR);
	}
}

void resetGrab(){
	if(SensorValue(potentiometerGrab) <= 3000){//10
		motor[grabMotor]= 100; // move the motor at a speed of 100
		waitUntil(SensorValue(potentiometerGrab) > 3000); // if the potentiometer is bigger than 2000
		stopMotor(grabMotor);// Stop the motor
	}else{
		stopMotor(grabMotor);
	}
}

void grabing(){
		motor[grabMotor]= -100;
		waitUntil(SensorValue(potentiometerGrab) < 20);
		stopMotor(grabMotor);
}

void droping(){
		motor[grabMotor]= 100;
		waitUntil(SensorValue(potentiometerGrab) > 3000);
		stopMotor(grabMotor);
}

void Picking(){
		motor[armMotorL]= 100;
		motor[armMotorR]= 100;
		waitUntil(SensorValue(potentiometerArm) >= 3000);
		stopMotor(armMotorL);
		stopMotor(armMotorR);
}

void firstMove(int speed) {
		motor[leftMotor] = speed;
		motor[rightMotor] = speed;
}

void turn(int speed){
	motor[leftMotor]= speed;
	motor[rightMotor]= -speed;
}

task main()
{
	resetArm();
	resetGrab();
	grabing();
	firstMove(63);
}