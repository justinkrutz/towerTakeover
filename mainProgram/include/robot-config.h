using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor BackLeftDrive;
extern motor FrontLeftDrive;
extern motor BackRightDrive;
extern motor FrontRightDrive;
extern motor Tray;
extern motor Arms;
extern motor IntakeLeft;
extern motor IntakeRight;
extern inertial Inertial;
extern signature FrontVision__SIG_1;
extern signature FrontVision__SIG_2;
extern signature FrontVision__SIG_3;
extern signature FrontVision__SIG_4;
extern signature FrontVision__SIG_5;
extern signature FrontVision__SIG_6;
extern signature FrontVision__SIG_7;
extern vision FrontVision;
extern line LineTrackerRight;
extern line LineTrackerLeft;
extern line LineTrackerTray;
extern bumper TipWheel;
extern led Flashlight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );