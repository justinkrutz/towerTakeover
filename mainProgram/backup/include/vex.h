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

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller Controller1;
extern vex::motor FrontRightMotor;
extern vex::motor FrontLeftMotor;
extern vex::motor BackRightMotor;
extern vex::motor BackLeftMotor;

/*----------------------------------------------------------------------------*/

extern void menuLcdDraw();
extern void controllerDraw();
extern void menuLcdTouch();
extern void autonIndicator();
// extern int selectedAuton();