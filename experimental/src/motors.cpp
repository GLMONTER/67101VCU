#include<motors.hpp>
#include<main.h>

void setDrive(int powerLeft, int powerRight, bool dummyForDebug)
{
	left = powerLeft;
	right = powerRight;
}
void setupMotors()
{
	// Clear both motor arrays
	for (unsigned int i = 0; i < kNumbOfTotalMotors; ++i) {
		gMotor[i].power = gMotor[i].curPower = motor[i] = 0;
		gMotor[i].powerScale = -1;
}

void updateMotors()
{
	for (unsigned int i = 0; i < kNumbOfTotalMotors; ++i)
		updateMotor(i);
}

void updateMotor(sMotor mot)
{
	mot.control = gMotor[mot].curPower = gMotor[mot].powerScale >= 0 ? round(gMotor[mot].power * gMotor[mot].powerScale) : gMotor[mot].power;
}