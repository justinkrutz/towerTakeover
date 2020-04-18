#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor TestMotor1 = motor(PORT2, ratio18_1, false);
motor TestMotor2 = motor(PORT7, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision = vision (PORT8, 50);
/*vex-vision-config:end*/
inertial Inertial = inertial(PORT9);

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