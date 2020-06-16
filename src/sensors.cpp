#include"sensors.hpp"

#define SIG 1

pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(1, -3181, -2279, -2730, 18811, 22221, 20516, 3.000, 0);
pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(2, 7711, 9645, 8678, -1089, 79, -505, 2.000, 0);
pros::Vision vSensor(8, pros::E_VISION_ZERO_CENTER);

//define to change sorting color
#define BLUE

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
	#ifdef BLUE
	vSensor.set_signature(2, &RED_SIG);
	#endif
	while(true)
	{
        //if the sorting system is disabled then don't attemp to sort.
        if(!SORT_SYS_ENABLE)
            break;
		//get the largest object(0), based on the signature passed in.
		pros::vision_object_s_t First_rtn = vSensor.get_by_sig(0, SIG);
		pros::vision_object_s_t Second_rtn = vSensor.get_by_sig(0, 2);

        /*the two if statements simply reverse the bottom lift to eject the ball if it is of the enemy color*/
		#ifdef BLUE
        //255 returns if no objects of stated signature is found.
		if(Second_rtn.signature != 255 && First_rtn.signature != 255)
		{
			if(First_rtn.y_middle_coord > Second_rtn.y_middle_coord)
			{
				vSensor.set_led(COLOR_GREEN);
				topLift.move(-127);
            	bottomLift.move(127);
				Lift.move(127);
			}
			else
			{
				vSensor.set_led(COLOR_GREEN);
				topLift.move(127);
            	bottomLift.move(127);
				Lift.move(127);
			}
			
		}
		else
		if(First_rtn.signature != 255)
		{
			vSensor.set_led(COLOR_BLUE);
			topLift.move(127);
            bottomLift.move(127);
			Lift.move(127);
		}
		else
		if(Second_rtn.signature != 255)
		{
			vSensor.set_led(COLOR_RED);
			topLift.move(-127);
            bottomLift.move(127);
			Lift.move(127);
		}
		#endif
	
		//so the program don't starve other tasks like updating the LCD
		pros::Task::delay(10);
	}
}