// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include <bits/stdc++.h>

#include "controllerMenu.h"
#include "driverControl.h"
#include "robotFunctions.h"


using namespace vex;

competition Competition;


void pre_auton( void ) {
  Controller1.ButtonB.pressed(abortEverything);
    // menuLcdDraw();
    // controllerDraw();
    // Brain.Screen.pressed(menuLcdTouch);

  ControllerMenu.printMenu();
  setCallbacksAutonSelect();
  waitUntil(Competition.isCompetitionSwitch() || Competition.isFieldControl());
  setCallbacksDriverMode();
}

void autonomous( void ) {

}

void usercontrol( void ) {

  while (1) {
    runButtons();
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