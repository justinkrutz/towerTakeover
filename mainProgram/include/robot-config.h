using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor intakeLeft;
extern motor intakeRight;
extern controller Controller2;
extern motor tray;
extern motor arms;
extern bumper goalButton;
extern inertial Inertial;
extern bumper trayButton;
extern motor backLeft;
extern motor frontLeft;
extern motor backRight;
extern motor frontRight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );