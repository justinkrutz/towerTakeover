using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern signature Vision__SIG_1;
extern signature Vision__SIG_2;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );