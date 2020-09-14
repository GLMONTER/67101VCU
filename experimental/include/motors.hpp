#include<main.h>
/* Structures */
typedef struct _sMotor
{
    pros::Motor control;
	int power;
	int curPower;
	float powerScale;
} sMotor; // Represent a single motor
pros::Motor left;
pros::Motor right;
/* Functions */
void setupMotors(); // Initilize all the motors
void updateMotors(); // Update the motor outputs
void updateMotor(sMotor mot); // Update a motor output
void setDrive(int powerLeft, int powerRight, bool dummyForDebug);
/* Variables */
sMotor gMotor[kNumbOfTotalMotors]; // The global motor array
