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

extern void autonInitialize();
extern void forwardFunction (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void strafeFunction  (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern void turnFunction    (double distance, int startSpeed, int maxSpeed, int endSpeed, bool waitForCompletion = true);
extern double forwardOutput;
extern double strafeOutput;
extern double turnOutput;
extern void autonStop();

extern double autoTray;
extern double autoArms;
extern double autoDrive;
extern double autoTurn;
extern double autoIntake;

extern void trayUp();
extern void trayDown();
extern void intakeSpin(double degrees, double percent);

extern vex::motor_group intake;

extern void autonRun(int auton);
#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)