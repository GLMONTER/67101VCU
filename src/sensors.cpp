#include"sensors.hpp"


pros::vision_signature_s_t BLUE_SIG = pros::Vision::signature_from_utility(1, -2721, -1159, -1940, 4661, 9577, 7119, 1.400, 0);
pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(2, 7711, 9645, 8678, -1089, 79, -505, 2.000, 0);
pros::Vision vSensor(6, pros::E_VISION_ZERO_CENTER);