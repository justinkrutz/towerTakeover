#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor intakeLeft = motor(PORT3, ratio18_1, false);
motor intakeRight = motor(PORT4, ratio18_1, true);
controller Controller2 = controller(partner);
motor tray = motor(PORT7, ratio36_1, false);
motor frontLeft = motor(PORT1, ratio18_1, false);
motor frontRight = motor(PORT2, ratio18_1, true);
motor backLeft = motor(PORT9, ratio18_1, false);
motor backRight = motor(PORT10, ratio18_1, true);
motor arms = motor(PORT8, ratio18_1, true);
bumper goalButton = bumper(Brain.ThreeWirePort.A);
limit leftIntakeSwitch = limit(Brain.ThreeWirePort.C);
limit rightIntakeSwitch = limit(Brain.ThreeWirePort.D);
/*vex-vision-config:begin*/
signature Vision__ORANGE_CUBE = signature (1, 1535, 8243, 4888, -2673, -1823, -2248, 0.9, 1);
signature Vision__GREEN_CUBE = signature (2, -6871, -6731, -6801, -3013, -2143, -2578, 11, 1);
signature Vision__PURPLE_CUBE = signature (3, -1, 1591, 794, 5077, 9047, 7062, 1.5, 0);
signature Vision__BLUE_GOAL = signature (5, -3107, -2499, -2803, 7801, 10955, 9378, 1.7, 0);
code Vision__TEST = code (Vision__GREEN_CUBE, Vision__ORANGE_CUBE );
vision Vision = vision (PORT6, 50, Vision__ORANGE_CUBE, Vision__GREEN_CUBE, Vision__PURPLE_CUBE, Vision__BLUE_GOAL);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}