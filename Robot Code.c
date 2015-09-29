#pragma config(Motor, port2, rightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port3, leftMotor, tmotorNormal, openLoop)
#pragma config(Motor, port4, armMotor, tmotorNormal, openLoop)
#pragma config(Motor, port5, clawServoRight, tmotorNormal, openLoop, reversed)
#pragma config(Motor, port6, clawServoLeft, tmotorNormal, openLoop)

/*
TEAM NUMBER: 266
JOYSTICKS (uses vertRT[Channel #]):
Ch1 - Right Joystick left/right
Ch2 - Right Joystick up/down
Ch3 - Left Joystick up/down
Ch4 - Left Joystick left/right

BUTTONS (uses Btn(#)(Letter):
7 & 8
Letters in clockwise order (starting from top): U, R, D, L

TRIGGERS (uses Btn(#)(Letter):
5 & 6
From top to bottom: U, D
*/

task main()
{
	motor[clawServoRight] = -63;
	motor[clawServoLeft] = -63;
	bool reverse = false;

	while (true)
	{
		if (vexRT[Btn8D])
			reverse = true;
		if (vexRT[Btn8D] && reverse == true)
			reverse = false;

		if (vexRT[Ch1])
		{
			//Moves robot forward/backward
			if (reverse == true)
			{
				//If the reverse button is toggled on, invert controls
				if (vexRT[Btn6D])
				{
					//Makes the robot go half speed as long as trigger button is pressed
					motor[rightMotor] = bMotorReflected[vexRT[Ch1]] / 2;
					motor[leftMotor] = bMotorReflected[vexRT[Ch1]] / 2;
				}
				else
				{
					//If trigger is not pressed, simply have the motor go normal speed
					motor[rightMotor] = bMotorReflected[vexRT[Ch1]];
					motor[leftMotor] = bMotorReflected[vexRT[Ch1]];
				}
			}
			else
			{
				//Otherwise, have robot normally move forward/back
				if (vexRT[Btn6D])
				{
					//Makes the robot go half speed as long as trigger button is pressed
					motor[rightMotor] = vexRT[Ch1] / 2;
					motor[leftMotor] = vexRT[Ch1] / 2;
				}
				else
				{
					//If trigger is not pressed, have robot go normal speed
					motor[rightMotor] = vexRT[Ch1];
					motor[leftMotor] = vexRT[Ch1];
				}
			}
		}
		else if (vexRT[Ch2])
		{
			//Spins robot in place
			if (vexRT[Btn6D])
			{
				//Slow down rotation if trigger button is pressed
				motor[rightMotor] = bMotorReflected[vexRT[Ch2]] / 2;
				motor[leftMotor] = vexRT[Ch2] / 2;
			}
			else
			{
				//If trigger is not pressed, have robot spin normal speed
				motor[rightMotor] = bMotorReflected[vexRT[Ch2]];
				motor[leftMotor] = vexRT[Ch2];
			}
		}

		if (vexRT[Ch3])
		{
			//Raise or lower arm
			if (vexRT[Btn6D])
				motor[armMotor] = vexRT[Ch3] / 2;	//Slows down arm movement if button 6D is pressed
			else
				motor[armMotor] = vexRT[Ch3];
		}

		if (vexRT[Btn5D])
		{
			//Closes the claw
			for (int i = -63; i <= 0; i++)	//Assuming -63 is the claw in open position
			{
				motor[clawServoRight] = i;
				motor[clawServoLeft] = i;
			}
		}
		else if (vexRT[Btn5U] && (motor[clawServoRight] == 0 && motor[clawServoLeft] == 0))
		{
			//Opens the claw
			for (int i = 0; i >= -63; i--)
			{
				motor[clawServoRight] = i;
				motor[clawServoLeft] = i;
			}
		}
	}
}
