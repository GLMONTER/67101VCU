#include "main.h"
#include"display/lvgl.h"



void initialize()
{
}

void disabled()
 {}


void competition_initialize()
 {}


void autonomous()
{}


//toggles for flywheel
static bool flyToggle = 0;
static bool flyPressed = 0;

//toggles for lift
static bool buttonToggleR = 0;
static bool buttonPressedR = 0;

static bool buttonToggleF = 0;
static bool buttonPressedF = 0;

void opcontrol()
{
	/*
	extern const lv_img_t seal;
	lv_obj_t * im = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(im, &seal);
	lv_obj_set_pos(im, 0, 0);
	lv_obj_set_drag(im, true);
	*/


	pros::Controller controller(pros::E_CONTROLLER_MASTER);

	pros::Motor leftDrive(10, pros::E_MOTOR_GEARSET_18, false);
	pros::Motor rightDrive(13, pros::E_MOTOR_GEARSET_18, true);

	pros::Motor Flywheel(12, pros::E_MOTOR_GEARSET_06, true);
	pros::Motor Lift(3, pros::E_MOTOR_GEARSET_06, true);
	pros::Motor leftLoader(2, pros::E_MOTOR_GEARSET_06, false);
	pros::Motor rightLoader(1, pros::E_MOTOR_GEARSET_06, true);
	pros::Motor topLift (30, pros::E_MOTOR_GEARSET_06, false);
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

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			rightLoader.move(127);
			leftLoader.move(127);
		}
		else
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			rightLoader.move(-127);
			leftLoader.move(-127);
		}
		else
		if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			//rightLoader.move(0);
			//leftLoader.move(0);
		}


		//go forward with drum
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			//if the forward button toggle isn't on then continute
			if(!buttonPressedF)
			{
				//actaully flip the toggle, this is why the type has to be int
				buttonToggleF = 1 - buttonToggleF;
				//changed button pressed to true
				buttonPressedF = 1;
				//change the backward toggle to false so we don't try to go backwards and forwards
				buttonToggleR = false;
			}
		}
		//switch back to normal buttton state but leave toggle on if button isn't pressed.
		else
			buttonPressedF = 0;

		//if our forward toggle is on, then eat the balls :D
		if(buttonToggleF == true)
		{
			Lift.move(90);
			rightLoader.move(-127);
			leftLoader.move(-127);
		}
		//check if other toggle is on if we need to really stop the motor
		else
		{
			if(!buttonToggleR && !buttonToggleF)
			{
				Lift.move(90);
				rightLoader.move(-127);
				leftLoader.move(-127);
			}
		}
		//go backwards with drum
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			//if we haven't pressed the button then toggle the button
			if(!buttonPressedR)
			{
				//actually toggle the button, this is why the type is int
				buttonToggleR = 1 - buttonToggleR;

				buttonPressedR = 1;

				//so we stop going forward.
				buttonToggleF = false;
			}
		}
	//else, then turn button pressed to false
		else
			buttonPressedR = 0;

		//if backward button toggle is on, then start the motor backward
		if(buttonToggleR == true)
		{
			Lift.move(-90);
			rightLoader.move(127);
			leftLoader.move(127);
		}
		//else, check if the forward toggle is off, then stop.
		else
		{
			if(!buttonToggleF && !buttonToggleR)
			{
				Lift.move(0);
				rightLoader.move(0);
				leftLoader.move(0);
			}
		}
		//delay program to allow draw calls to display and sensor polling.
		pros::Task::delay(10);
	}
}
