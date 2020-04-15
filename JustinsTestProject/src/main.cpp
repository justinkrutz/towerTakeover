// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Controller2          controller                    
// TestMotor1           motor         2               
// TestMotor2           motor         7               
// Vision               vision        8               
// Inertial             inertial      9               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"

#include <bits/stdc++.h>

#include "controller-menu.h"
#include "controller-buttons.h"
#include "robot-functions.h"


using namespace vex;

competition Competition;


void pre_auton( void ) {
  ControllerMenu::printMenu();
  ControllerMenu::loadSettings();
  ControllerMenu::setCallbacks();
  (thread (RobotFunctions::checkForWarnings));
  waitUntil(Competition.isCompetitionSwitch() || Competition.isFieldControl());
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("Connected");
  ControllerMenu::checkForAuton();
  RobotFunctions::setCallbacks();
}

void autonomous( void ) {
  ControllerMenu::runAuton();
}

void usercontrol( void ) {
  while (1) {
    ControllerButtons::runButtons();
    task::sleep(10); //Sleep task for a short amount of time to prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
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