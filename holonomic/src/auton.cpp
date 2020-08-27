#include"main.h"
pros::Imu imu(18);

/*
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

void runAuton()
{
    
    chassis->setMaxVelocity(100);
  

}
