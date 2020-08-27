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
auto chassis = ChassisControllerBuilder()
//motor comments not correct
    .withMotors(
        -11,  // Top left
        20, // Top right (reversed)
        -1, // Bottom right (reversed)
        10   // Bottom left
    )
	 .withDimensions(AbstractMotor::gearset::green, {{4_in, 8.5_in}, imev5GreenTPR})
	.withOdometry()
	.build();
void autonomous() {
		chassis->setMaxVelocity(20);

	chassis->moveDistance(1_ft);
}

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
void opcontrol() 
{
	pros::Controller controller(pros::E_CONTROLLER_MASTER);

	pros::Motor leftLoader(12, pros::E_MOTOR_GEARSET_06, false);
	pros::Motor rightLoader(4, pros::E_MOTOR_GEARSET_06, true);

	pros::Motor rightFront(11, true);
	pros::Motor leftFront(20, false);
	pros::Motor rightBack(1, true);
	pros::Motor leftBack(9, false);
	
	while (true) 
	{
		int32_t ch1 = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		int32_t ch2 = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		int32_t ch3 = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int32_t ch4 = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		leftFront.move(ch3 + ch1 + ch4);
		rightFront.move(ch3 - ch1 - ch4);
		leftBack.move(ch3 + ch1 - ch4);
		rightBack.move(ch3 - ch1 + ch4);
		
		//LOADING SYSTEM.
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			rightLoader.move(127);
			leftLoader.move(127);
		}
		else
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			rightLoader.move(-127);
			leftLoader.move(-127);
		}
		else
		if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			rightLoader.move(0);
			leftLoader.move(0);
		}

		pros::delay(10);
	}
}
