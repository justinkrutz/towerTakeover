#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor intakeLeft = motor(PORT12, ratio18_1, false);
motor intakeRight = motor(PORT13, ratio18_1, true);
controller Controller2 = controller(partner);
motor tray = motor(PORT21, ratio36_1, false);
motor arms = motor(PORT14, ratio18_1, true);
bumper goalButton = bumper(Brain.ThreeWirePort.A);
inertial Inertial = inertial(PORT2);
bumper trayButton = bumper(Brain.ThreeWirePort.E);
motor backLeft = motor(PORT7, ratio18_1, false);
motor frontLeft = motor(PORT8, ratio18_1, false);
motor backRight = motor(PORT9, ratio18_1, true);
motor frontRight = motor(PORT10, ratio18_1, true);
/*vex-vision-config:begin*/
signature Vision__SIG_1 = signature (1, -7081, -6137, -6609, -4419, -3089, -3754, 6.6, 0);
signature Vision__SIG_2 = signature (2, 7679, 8347, 8013, -3493, -2569, -3031, 3, 0);
signature Vision__SIG_3 = signature (3, 313, 1063, 688, 4757, 6865, 5811, 3, 0);
signature Vision__SIG_4 = signature (4, -2699, -2105, -2402, 7879, 9039, 8459, 4.3, 0);
vision Vision = vision (PORT15, 100, Vision__SIG_1, Vision__SIG_2, Vision__SIG_3, Vision__SIG_4);
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