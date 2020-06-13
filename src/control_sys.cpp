#include"control_sys.hpp"


pros::Motor leftDrive(10, pros::E_MOTOR_GEARSET_18, false);
pros::Motor rightDrive(13, pros::E_MOTOR_GEARSET_18, true);

pros::Motor Flywheel(12, pros::E_MOTOR_GEARSET_06, true);
pros::Motor Lift(3, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftLoader(2, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightLoader(1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor topLift (30, pros::E_MOTOR_GEARSET_06, false);
pros::Motor bottomLift (30, pros::E_MOTOR_GEARSET_06, false);

bool SORT_SYS_ENABLE = true;
//this function will sort the balls based on the color signature passed in. 
//The task will start at the beginning of the program with the correct ball color to start.
void sort(void* sigPass)
{
    pros::vision_signature_s_t sig =  *reinterpret_cast<pros::vision_signature_s_t*>(sigPass);
	//basically resetting the vision sensor.
	vSensor.clear_led();

	//set SIG as sig so SIG can be referenced later
	vSensor.set_signature(SIG, &sig);

	while(true)
	{
        //if the sorting system is disabled then don't attemp to sort.
        if(!SORT_SYS_ENABLE)
            break;
		//get the largest object(0), based on the signature passed in.
		pros::vision_object_s_t rtn = vSensor.get_by_sig(0, SIG);
		
        /*the two if statements simply reverse the bottom lift to eject the ball if it is of the enemy color*/

        //255 returns if no objects of stated signature is found.
		if(rtn.signature == 255)
		{
			topLift.move(127);
            bottomLift.move(-127);
		}
		if(rtn.signature != 255)
		{
			topLift.move(127);
            bottomLift.move(127);
		}
		//so the program don't starve other tasks like updating the LCD
		pros::Task::delay(10);
	}
}

//toggles for lift
static bool buttonToggleR = 0;
static bool buttonPressedR = 0;

static bool buttonToggleF = 0;
static bool buttonPressedF = 0;

void sortFailsafe()
{
    //go forward with drum
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
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
        topLift.move(127);
        bottomLift.move(127);
    }
    //check if other toggle is on if we need to really stop the motor
    else
    {
        if(!buttonToggleR && !buttonToggleF)
        {
            topLift.move(127);
            bottomLift.move(127);        
        }
    }
    //go backwards with drum
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
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
        topLift.move(-127);
        bottomLift.move(-127);  
    }
    //else, check if the forward toggle is off, then stop.
    else
    {
        if(!buttonToggleF && !buttonToggleR)
        {
            topLift.move(0);
            bottomLift.move(0);  
        }
    }
}