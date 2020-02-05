using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor wheelFrontLeft;
extern motor wheelFrontRight;
extern motor wheelBackLeft;
extern motor wheelBackRight;
extern controller Controller1;
extern motor intakeLeft;
extern motor intakeRight;
extern controller Controller2;
extern motor tray;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );