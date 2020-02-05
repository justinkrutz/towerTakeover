#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor wheelFrontLeft = motor(PORT1, ratio18_1, false);
motor wheelFrontRight = motor(PORT2, ratio18_1, true);
motor wheelBackLeft = motor(PORT9, ratio18_1, false);
motor wheelBackRight = motor(PORT10, ratio18_1, true);
controller Controller1 = controller(primary);
motor intakeLeft = motor(PORT11, ratio18_1, true);
motor intakeRight = motor(PORT20, ratio18_1, false);
controller Controller2 = controller(partner);
motor tray = motor(PORT8, ratio36_1, false);
inertial Inertial = inertial(PORT3);

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