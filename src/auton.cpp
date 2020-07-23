#include"main.h"
pros::Imu imu(18);

void gyroTurn(float deg)
{
	leftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    float error = 10.0;
    float integral = 0.0;
    float derivative = 0.0;
    float perror = 0.0;
    float value = 0.0;

    float target = deg;
    float Ki = -0.0005;
    float Kd = -1.0;
    float Kp = -1.0;

    while (abs(error) > 0.1 || leftDrive.get_actual_velocity() > 0.1)
    {
        pros::lcd::print(0, "val: %f\n", imu.get_yaw());
        error =  target - imu.get_yaw();
        printf("%f \n", error);
        integral = integral + error;
        if (abs(error) < 2)
        {
            integral = 0.0;
        }
        derivative = error - perror;
        perror = error;
        value = (integral*Ki) + (derivative*Kd) + (error*Kp);

        leftDrive.move(-value);
        rightDrive.move(value);

        pros::delay(5);
    }
    leftDrive.move(0);
    rightDrive.move(0);
}

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors(1, 10) // left motor is 1, right motor is 2 (reversed)
    
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.25_in}, quadEncoderTPR})

    .withSensors(
        ADIEncoder{'C', 'D', true}, // left encoder in ADI ports A & B
        ADIEncoder{'A', 'B', true}  // right encoder in ADI ports C & D (reversed)
        //ADIEncoder{'E', 'F'}  // middle encoder in ADI ports E & F
    )
    .withGains(
        {0.005, 0.0001, 0.00005}, // distance controller gains
        {0.003, 0, 0.0001}, // turn controller gains
        {0.003, 0.0001, 0.0005}  // angle controller gains (helps drive straight)
    )
    // green gearset, tracking wheel diameter (2.75 in), track (7 in), and TPR (360)
    // 1 inch middle encoder distance, and 2.75 inch middle wheel diameter
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

void runAuton()
{
    pros::lcd::initialize();
    chassis->setMaxVelocity(80);
    chassis->moveDistance(1_ft);
    gyroTurn(90);
    chassis->moveDistance(1_ft);

}
