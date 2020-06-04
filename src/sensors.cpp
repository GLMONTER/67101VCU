#include"sensors.hpp"

//used as a reference to get the signature
#define SIG 1

//vision sensor object.
pros::Vision vSensor(6, pros::E_VISION_ZERO_CENTER);

//simply a function that reads the signaure(sig) passed in, and looks at it within the given range(MAX_LEFT, MAX_RIGHT).
void vision_READ(pros::vision_signature_s_t sig, int MAX_LEFT, int MAX_RIGHT, bool aton)
{
  //clears the color stack frame
	vSensor.clear_led();

  //set SIG as sig so SIG can be referenced later
  vSensor.set_signature(SIG, &sig);

  //update the position of the signature, if it is out of range, ajust the robot,
  //if it is good, stop the motors and break out of the loop.
	while(true)
	{
		//get the largest object(0), based on the signature passed in.
		//we call this every update to get the new position of the object
		pros::vision_object_s_t rtn = vSensor.get_by_sig(0, SIG);
    std::cout<<rtn.x_middle_coord<<std::endl;

		//so we don't starv other tasks like updating the LCD
		pros::Task::delay(20);
	}
}
