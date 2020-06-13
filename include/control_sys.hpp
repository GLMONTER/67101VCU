#include"main.h"

extern bool SORT_SYS_ENABLE;
void sortFailsafe();
void sort(void* sigPass);

extern pros::Controller controller;

extern pros::Motor leftDrive;
extern pros::Motor rightDrive;

extern pros::Motor Flywheel;
extern pros::Motor bottomLift;
extern pros::Motor topLift;

extern pros::Motor leftLoader;
extern pros::Motor rightLoader;