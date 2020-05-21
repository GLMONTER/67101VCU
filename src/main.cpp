#include "main.h"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

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
static bool flyToggle = 0;
static bool flyPressed = 0;


void opcontrol()
{
	pros::Controller controller(pros::E_CONTROLLER_MASTER);

	pros::Motor leftDrive(1, pros::E_MOTOR_GEARSET_18, false);
	pros::Motor rightDrive(2, pros::E_MOTOR_GEARSET_18, true);

	pros::Motor Flywheel(3, pros::E_MOTOR_GEARSET_06, false);
	pros::Motor Lift(4, pros::E_MOTOR_GEARSET_06, false);
	pros::Motor leftLoader(5, pros::E_MOTOR_GEARSET_06, false);
	pros::Motor rightLoader(5, pros::E_MOTOR_GEARSET_06, true);

	while(true)
	{
		leftDrive.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		rightDrive.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

		//FLYWHEEL CONTROLER
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
	{
		if(!flyPressed)
		{
			flyToggle = 1 - flyToggle;

			flyPressed = 1;
		}
	}
	else
		flyPressed = 0;

	if(flyToggle)
	{
		Flywheel.move(127);
	}
	else
  {
		Flywheel.move(0);
  }

	//LOADING SYSTEM.
	}
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
	{
		Lift.move(127);

		rightLoader.move(127);
		leftLoader.move(127);
	}
	else
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
	{
		Lift.move(-127);

		rightLoader.move(-127);
		leftLoader.move(-127);
	}
	else if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
	{
		Lift.move(0);

		rightLoader.move(0);
		leftLoader.move(0);
	}
	pros::Task::delay(10);

}
