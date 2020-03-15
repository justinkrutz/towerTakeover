/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       3018E                                                     */
/*    Created:      Wed Mar 04 2020                                           */
/*    Description:  Master program for 3018E's 2019-2020 season               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Controller2          controller                    
// BackLeftDrive        motor         7               
// FrontLeftDrive       motor         8               
// BackRightDrive       motor         9               
// FrontRightDrive      motor         10              
// Tray                 motor         21              
// Arms                 motor         11              
// IntakeLeft           motor         12              
// IntakeRight          motor         13              
// Inertial             inertial      2               
// FrontVision          vision        15              
// LineTrackerRight     line          A               
// LineTrackerLeft      line          E               
// LineTrackerTray      line          C               
// TipWheel             bumper        D               
// Flashlight           led           H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include "menuSystem.h"
#include "autonStructure.h"
#include "autonRoutines.h"
#include "driverControl.h"

using namespace vex;
competition Competition;
motor_group Intake ( IntakeLeft, IntakeRight );
motor_group Drivetrain ( FrontLeftDrive, FrontRightDrive, BackLeftDrive, BackRightDrive );

// vision::signature CUBE_ORANGE (1, 6343, 7765, 7054, -2843, -1635, -2239, 3.000, 0);
// vision::signature CUBE_GREEN (2, -6065, -3709, -4887, -3385, -1461, -2423, 2.500, 0);
// vision::signature CUBE_PURPLE (3, 1401, 2161, 1781, 7625, 9415, 8520, 3.000, 0);
// vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision vision1 ( PORT1, 60, CUBE_ORANGE, CUBE_GREEN, CUBE_PURPLE, SIG_4, SIG_5, SIG_6, SIG_7 );




/*===========================================================================*/

void pre_auton( void ) {
  Inertial.calibrate();
  Flashlight.off();

  Tray.setStopping(hold);
  Arms.setStopping(hold);
  Intake.setStopping(hold);
  setButtonCallbacks();







  (task ( motorTask ));
  autonTaskStart();

  menuLcdDraw();
  controllerDraw();
  Brain.Screen.pressed(menuLcdTouch);

  waitUntil(!(!Competition.isAutonomous() || !Competition.isEnabled()));
  Brain.Screen.pressed(unassign);
}

/*===========================================================================*/

void autonomous( void ) {
  autonIndicator();
  autonReset();
  autonRun(currentPage);

  wait(2, sec);

  return;
}

/*===========================================================================*/

void usercontrol( void ) {
  autonReset();
  Drivetrain.setStopping(coast);

  Arms.setPosition(-73, degrees);
  while(Arms.position(deg) < 0) {
  autoArms = 5;
  task::sleep(5);
  }
  autoArms = 0;

  while (1) {
    drivetrainControl();
    manualControl();
    controllerInfo();
    task::sleep(5); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

/*===========================================================================*/

int main() {
  vexcodeInit();
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );

  //Run the pre-autonomous function. 
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(1) {
    task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }    
}