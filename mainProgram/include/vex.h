/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

/*----------------------------------------------------------------------------*/

// extern vex::competition Competition;
// extern vex::brain Brain;
// extern vex::controller Controller1;
// extern vex::motor FrontRightMotor;
// extern vex::motor FrontLeftMotor;
// extern vex::motor BackRightMotor;
// extern vex::motor BackLeftMotor;

/*----------------------------------------------------------------------------*/

extern void menuLcdDraw();
extern void controllerDraw();
extern void menuLcdTouch();
extern void autonIndicator();
extern int currentPage;

extern double headingDeg;
extern void autonInitialize();
extern void autonTaskStart();
extern void forwardFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void strafeFunction  (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void turnFunction    (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern double forwardOutput;
extern double strafeOutput;
extern double turnOutput;
extern double headingDeg;
extern bool gyroActive;

extern void skillsOne();

struct rampStruct
{
  double distance;
  int startSpeed;
  int maxSpeed;
  int endSpeed;
  bool isMoving;
};

extern rampStruct forwardStruct;
extern rampStruct strafeStruct;
extern rampStruct turnStruct;

extern int allianceColor;


extern bool autoAbort;

extern double autoTray;
extern double autoArms;
extern double autoDrive;
extern double autoTurn;
extern void visionDetectFunction (bool turn, double turnP = 0.5, double time = 0);
extern bool greenToggle;
extern bool orangeToggle;
extern bool purpleToggle;

extern void goalDrive();
extern void trayUp();
extern void trayDown();
extern void intakeSpin(double degrees, double percent);
extern void armsMove (double degrees, double percent, vex::brakeType brakeType = vex::hold);
extern void armsDown();
extern void armsLow();
extern void armsHigh();
extern double autoIntake;

extern vex::motor_group intake;
extern vex::competition Competition;
extern vex::motor_group Drivetrain;

extern void autonRun(int auton);
#include "robot-config.h"

extern double gyroYawStart;
#define gyroYaw ((Inertial.rotation(deg) - gyroYawStart))

#define forwardDistanceP (28.647889757)
#define strafeDistanceP (32.243767313)
#define strafeSpeedP (1.12551980572)

#define forwardDistance ((frontLeft.rotation(deg) + backLeft.rotation(deg) + frontRight.rotation(deg) + backRight.rotation(deg)) / 4 / forwardDistanceP)
#define strafeDistance ((frontLeft.rotation(deg) - backLeft.rotation(deg) + backRight.rotation(deg) - frontRight.rotation(deg)) / 4 / strafeDistanceP)

#define blueAlliance 1
#define redAlliance -1

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)