#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor BackLeftDrive = motor(PORT7, ratio18_1, false);
motor FrontLeftDrive = motor(PORT8, ratio18_1, false);
motor BackRightDrive = motor(PORT9, ratio18_1, true);
motor FrontRightDrive = motor(PORT10, ratio18_1, true);
motor Tray = motor(PORT21, ratio36_1, true);
motor Arms = motor(PORT11, ratio18_1, true);
motor IntakeLeft = motor(PORT12, ratio18_1, false);
motor IntakeRight = motor(PORT13, ratio18_1, true);
inertial Inertial = inertial(PORT2);
/*vex-vision-config:begin*/
vision FrontVision = vision (PORT15, 50);
/*vex-vision-config:end*/
line LineTrackerRight = line(Brain.ThreeWirePort.A);
line LineTrackerLeft = line(Brain.ThreeWirePort.E);
line LineTrackerTray = line(Brain.ThreeWirePort.C);
bumper TipWheel = bumper(Brain.ThreeWirePort.D);
led Flashlight = led(Brain.ThreeWirePort.H);

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