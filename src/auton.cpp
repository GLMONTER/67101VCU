#include"main.h"

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors(1, 10) // left motor is 1, right motor is 2 (reversed)
    
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 13.25_in}, quadEncoderTPR})

    .withSensors(
        ADIEncoder{'C', 'D', true}, // left encoder in ADI ports A & B
        ADIEncoder{'A', 'B', true}  // right encoder in ADI ports C & D (reversed)
        //ADIEncoder{'E', 'F'}  // middle encoder in ADI ports E & F
    )
    .withGains(
        {0.0025, 0.0005, 0.0001}, // distance controller gains
        {0.003, 0, 0.0001}, // turn controller gains
        {0.0025, 0.001, 0.0001}  // angle controller gains (helps drive straight)
    )
    // green gearset, tracking wheel diameter (2.75 in), track (7 in), and TPR (360)
    // 1 inch middle encoder distance, and 2.75 inch middle wheel diameter
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

void runAuton()
{
  chassis->moveDistance(1_ft);
}
