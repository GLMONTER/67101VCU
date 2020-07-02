#include"sensors.hpp"

#define ALLIANCE_SIG 1
#define ENEMEY_SIG 2

pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(1, -3181, -2279, -2730, 18811, 22221, 20516, 3.000, 0);
pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(2, 7711, 9645, 8678, -1089, 79, -505, 2.000, 0);
pros::Vision vSensor(8, pros::E_VISION_ZERO_CENTER);

pros::ADIDigitalIn topLimit('A');
extern bool canLimit;
//define the alliance color to sort the correct ball color.
#define BLUE

bool SORT_SYS_ENABLE = true;
//this function will sort the balls based on the color signature passed in. 
//The task will start at the beginning of the program with the correct ball color to start.
void sort(void* sigPass)
{
    pros::vision_signature_s_t sig =  *reinterpret_cast<pros::vision_signature_s_t*>(sigPass);
	//resetting vision sensor LED color.
	vSensor.clear_led();

	//set the red and blue signatures to be referenced later.
	vSensor.set_signature(ALLIANCE_SIG, &sig);
	#ifdef BLUE
	vSensor.set_signature(ENEMEY_SIG, &RED_SIG);
	#else
	vSensor.set_signature(ENEMEY_SIG, &BLUE_SIG);
	#endif

	while(true)
	{
		if(topLimit.get_value() && canLimit)
		{
			topLift.move(0);
            bottomLift.move(0);
			Lift.move(0);
			continue;
		}
        //if the sorting system is disabled then don't attemp to sort.
        if(!SORT_SYS_ENABLE)
            continue;
	
		//get the largest object(0), based on the signature passed in.
		pros::vision_object_s_t First_rtn = vSensor.get_by_sig(0, ALLIANCE_SIG);
		pros::vision_object_s_t Second_rtn = vSensor.get_by_sig(0, ENEMEY_SIG);

        //these if statements simply sort out the enemy ball colors
		
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
			#ifdef BLUE
			vSensor.set_led(COLOR_BLUE);
			#else
			vSensor.set_led(COLOR_RED);
			#endif
			topLift.move(127);
            bottomLift.move(127);
			Lift.move(127);
		}
		else
		if(Second_rtn.signature != 255)
		{
			#ifdef BLUE
			vSensor.set_led(COLOR_RED);
			#else
			vSensor.set_led(COLOR_BLUE);
			#endif
			topLift.move(-127);
            bottomLift.move(127);
			Lift.move(127);
		}
		else
		{
			vSensor.set_led(COLOR_LIGHT_CORAL);

			topLift.move(127);
            bottomLift.move(127);
			Lift.move(127);
		}
		
	
		//make the thread sleep to prevent other threads from being starved of resources.
		pros::Task::delay(10);
	}
}