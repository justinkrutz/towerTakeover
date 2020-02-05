using namespace vex;

extern brain Brain;

using signature = vision::signature;
using code = vision::code;

// VEXcode devices
extern controller Controller1;
extern motor intakeLeft;
extern motor intakeRight;
extern controller Controller2;
extern motor tray;
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern motor arms;
extern bumper goalButton;
extern limit leftIntakeSwitch;
extern limit rightIntakeSwitch;
extern signature Vision__ORANGE_CUBE;
extern signature Vision__GREEN_CUBE;
extern signature Vision__PURPLE_CUBE;
extern signature Vision__RED_GOAL;
extern signature Vision__BLUE_GOAL;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern code Vision__TEST;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );