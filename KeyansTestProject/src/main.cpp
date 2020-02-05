#include "vex.h"

//this is an edit from my phone

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// intakeLeft           motor         3               
// intakeRight          motor         4               
// Controller2          controller                    
// tray                 motor         7               
// frontLeft            motor         1               
// frontRight           motor         2               
// backLeft             motor         9               
// backRight            motor         10              
// arms                 motor         8               
// goalButton           bumper        A               
// leftIntakeSwitch     limit         C               
// rightIntakeSwitch    limit         D               
// Vision               vision        6               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
vex::competition Competition;


// vision::signature CUBE_ORANGE (1, 6343, 7765, 7054, -2843, -1635, -2239, 3.000, 0);
// vision::signature CUBE_GREEN (2, -6065, -3709, -4887, -3385, -1461, -2423, 2.500, 0);
// vision::signature CUBE_PURPLE (3, 1401, 2161, 1781, 7625, 9415, 8520, 3.000, 0);
// vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vex::vision vision1 ( vex::PORT1, 60, CUBE_ORANGE, CUBE_GREEN, CUBE_PURPLE, SIG_4, SIG_5, SIG_6, SIG_7 );


/*===========================================================================*/

void pre_auton( void ) {

}

/*===========================================================================*/

void autonomous( void ) {


  
  return; //Idk if you need this at the end but it won't hurt
}

/*===========================================================================*/

void usercontrol( void ) {

  while (1) {
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }    
       
}