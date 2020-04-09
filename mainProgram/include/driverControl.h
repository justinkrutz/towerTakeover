#define setFunction( function ) [](void) {(task (function));}

#define armsPosDown 0
#define armsPosLow 1
#define armsPosHigh 2

#define cubeGreen FrontVision__SIG_1
#define cubeOrange FrontVision__SIG_2
#define cubePurple FrontVision__SIG_3

extern double autoTray;
extern double autoArms;
extern double autoDrive;
extern double autoTurn;
extern int visionDetectFunction (bool turn, double turnP = 0.5, double time = 0);
extern bool greenToggle;
extern bool orangeToggle;
extern bool purpleToggle;
extern double stickForward;
extern double stickStrafe;
extern double stickTurn;
extern double autoTray;
extern double autoArms;
extern double autoDrive;
extern double autoTurn;
extern double autoIntake;
extern double rampDrive;
extern double rampTurn;
extern double visionTurn;
extern double visionStrafe;
extern double lastTime;
extern int armsPos;
extern bool trayMoving;
extern bool armsMoving;
extern bool intakeMoving;
extern bool turboTurn;
extern bool greenToggle;
extern bool orangeToggle;
extern bool purpleToggle;
extern bool Button;
extern double trayStick;
extern double trayButton;
extern double intakeStick;
extern double intakeStickTwist;
extern double armsStick;
extern double driveSpeed;
extern int motorTask();
extern int intakeSpin(double degrees, double percent);
extern int intakeIn();
extern int intakeOut();
extern int intakeOutSlow();
extern int goalIntake();
extern int goalDrive ();
extern int trayUpDrive ();
extern int trayUp(); 
extern int trayDownDrive();
extern int trayDown();
extern int trayStart ();
extern int trayStop ();
extern int armsMove (double degrees, double percent, vex::brakeType brakeType);
extern int armsDown ();
extern int armsHigh ();
extern int armsLow ();
extern int greenToggleButton ();
extern int purpleToggleButton ();
extern int orangeToggleButton ();
extern int visionDetectFunction (bool turn, double turnP, double time);
extern int visionTurnFunction ();
extern int visionStrafeFunction ();
extern int trayReset ();
extern int armsReset ();
extern int driveSlow();
extern int setButtonCallbacks();
extern void unassign();
extern void drivetrainControl();
extern void manualControl();
extern void controllerInfo();