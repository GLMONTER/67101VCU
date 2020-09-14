#include "main.h"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
//distance from tracking center to center of left tracking wheel
float sSubL = 0.0f;

//distance from tracking center to center of right tracking wheel
float sSubR = 0.0f;

//distance from tracking center to rear back tracking wheel
float sSubS = 0.0f;


//TYPES FOR VECTOR ARE UNKNOWN AT THE MOMENT
//previous global position vector
auto dSubZero = 0.0f;

//previous global orientation
auto ZeroSubZero = 0.0f;

//global orientation at last reset
auto ZeroSubR = 0.0f;

double previousLeftEncoder = 0;
double previousRightEncoder = 0;

double deltaRight = 0.0;
double deltaLeft = 0.0;
double deltaStrafe = 0.0;

double leftWheelDiameter = 4.25;
double rightWheelDiameter = 4.25;
double middleWheelDiameter = 4.25;

pros::ADIEncoder leftEncoder(1, 2, false);
pros::ADIEncoder rightEncoder(1, 2, false);
extern void updateTimer();
void opcontrol() {
	//get the new encoder distance
    double currentRight = rightEncoder.get_value();
    double currentLeft = leftEncoder.get_value();

    //change in encoder values since last tick
    deltaRight = std::abs(currentRight - previousRightEncoder);
    deltaLeft = std::abs(currentLeft - previousLeftEncoder);

    std::cout<<currentRight<<std::endl;
    pros::Task::delay(10);
    updateTimer();
}
