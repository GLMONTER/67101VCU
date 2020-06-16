#include "main.h"
#include"display/lvgl.h"

void initialize()
{

}

void disabled()
{
	
}


void competition_initialize()
{

}


void autonomous()
{

}


//toggles for flywheel
static bool flyToggle = 0;
static bool flyPressed = 0;

//toggles for sorting system
static bool sortToggle = 1;
static bool sortPressed = 0;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol()
{
	//load vaquita image from SD Card
	lv_obj_t* image = lv_img_create(lv_scr_act(), NULL);
	//the root path of the card is always /usd/
	lv_img_set_src(image, "/usd/vaquita.bin");
	lv_obj_set_pos(image, 0, 0);
	lv_obj_set_drag(image, true);

	
	//start the async sort task to begin sorting during driver control.
	pros::Task sortTask(sort, reinterpret_cast<void*>(&BLUE_SIG),"test");
	

	while(true)
	{
		//set the motor power of the drivetrain equal to the controller joysticks.
		leftDrive.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		rightDrive.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

		//a failsafe for the sorting system
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			if(!sortPressed)
			{
				sortToggle = 1 - sortToggle;

				sortPressed = 1;
			}
		}
		else
			sortPressed = 0;

		if(sortToggle)
		{
			SORT_SYS_ENABLE = true;
		}
		else
		{
			SORT_SYS_ENABLE = false;
			sortFailsafe();
		}


		//FLYWHEEL CONTROLER
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			if(!flyPressed)
			{
				flyToggle = 1 - flyToggle;

				flyPressed = 1;
			}
		}
		else
			flyPressed = 0;

		//if the toggle is enabled then start the flywheel, if disabled then stop it.s
		if(flyToggle)
		{
			Flywheel.move(127);
		}
		else
		{
			Flywheel.move(0);
		}

		//LOADING SYSTEM.
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			rightLoader.move(127);
			leftLoader.move(127);
			//Lift.move(127);
		}
		else
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			rightLoader.move(-127);
			leftLoader.move(-127);
			//Lift.move(-127);

		}
		else
		if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			rightLoader.move(0);
			leftLoader.move(0);
			//Lift.move(0);

		}

		//delay program to allow draw calls to display and sensor polling.
		pros::Task::delay(10);
	}
}
