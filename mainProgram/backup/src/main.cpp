#include "vex.h"

using namespace vex;

/*----------------------------------------------------------------------------*/

vex::competition Competition;
vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor FrontRightMotor  = vex::motor( vex::PORT1);
vex::motor FrontLeftMotor   = vex::motor( vex::PORT2, true);
vex::motor BackRightMotor   = vex::motor( vex::PORT9);
vex::motor BackLeftMotor    = vex::motor( vex::PORT10, true);

/*----------------------------------------------------------------------------*/

void pre_auton( void ) {
  menuLcdDraw();
  controllerDraw();
  while (!Competition.isAutonomous() || !Competition.isEnabled()) {
    menuLcdTouch();
    vex::task::sleep(20);
  }
}

/*----------------------------------------------------------------------------*/

void autonomous( void ) {
  autonIndicator();
}

/*----------------------------------------------------------------------------*/

void usercontrol( void ) {

  while (1) {
      double axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000);
      double axis4Prop = (pow(Controller1.Axis4.position(), 3) / 10000);

      FrontLeftMotor.spin  (vex::directionType::fwd, (axis3Prop - axis4Prop), vex::velocityUnits::pct); 
      FrontRightMotor.spin (vex::directionType::fwd, (axis3Prop + axis4Prop), vex::velocityUnits::pct);
      BackLeftMotor.spin   (vex::directionType::fwd, (axis3Prop - axis4Prop), vex::velocityUnits::pct); 
      BackRightMotor.spin  (vex::directionType::fwd, (axis3Prop + axis4Prop), vex::velocityUnits::pct);
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

/*----------------------------------------------------------------------------*/

int main() {
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