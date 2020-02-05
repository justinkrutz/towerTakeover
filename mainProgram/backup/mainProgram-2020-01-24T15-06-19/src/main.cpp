#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// wheelFrontLeft       motor         1               
// wheelFrontRight      motor         2               
// wheelBackLeft        motor         9               
// wheelBackRight       motor         10              
// Controller1          controller                    
// intakeLeft           motor         11              
// intakeRight          motor         20              
// Controller2          controller                    
// tray                 motor         8               
// Inertial             inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
vex::competition Competition;

bool arcade = true;
bool edgeArcade = false;


/*----------------------------------------------------------------------------*/

void pre_auton( void ) {
  menuLcdDraw();
  controllerDraw();
  // Inertial.calibrate();
  Controller1.ButtonR1.pressed(void (*callback)())

  while (!Competition.isAutonomous() || !Competition.isEnabled()) {
    menuLcdTouch();
    // Controller1.Screen.clearLine();
    // Controller1.Screen.print(Inertial.gyroRate(zaxis, dps));
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
      double axis2Prop = (pow(Controller1.Axis2.position(), 3) / 10000);
      double axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000);
      double axis4Prop = (pow(Controller1.Axis1.position(), 3) / 10000);
      // double axis2Prop = (Controller1.Axis2.position());
      // double axis3Prop = (Controller1.Axis3.position());
      // double axis4Prop = (Controller1.Axis4.position());

      if (Controller1.ButtonX.pressing() && !edgeArcade) {
        arcade = !arcade;
      } else if (!Controller1.ButtonX.pressing() && edgeArcade) {
        edgeArcade = false;
      }
      if (arcade) {
        wheelFrontLeft.spin  (vex::directionType::fwd, (axis3Prop + axis4Prop), vex::velocityUnits::pct); 
        wheelFrontRight.spin (vex::directionType::fwd, (axis3Prop - axis4Prop), vex::velocityUnits::pct);
        wheelBackLeft.spin   (vex::directionType::fwd, (axis3Prop + axis4Prop), vex::velocityUnits::pct); 
        wheelBackRight.spin  (vex::directionType::fwd, (axis3Prop - axis4Prop), vex::velocityUnits::pct);
      } else {
        wheelFrontLeft.spin  (vex::directionType::fwd, (axis3Prop), vex::velocityUnits::pct); 
        wheelFrontRight.spin (vex::directionType::fwd, (axis2Prop), vex::velocityUnits::pct);
        wheelBackLeft.spin   (vex::directionType::fwd, (axis3Prop), vex::velocityUnits::pct); 
        wheelBackRight.spin  (vex::directionType::fwd, (axis2Prop), vex::velocityUnits::pct);
      }
      intakeRight.spin(fwd, Controller2.Axis3.position(), percent);
      intakeLeft.spin(fwd, Controller2.Axis3.position(), percent);
      tray.spin(fwd, Controller2.Axis2.position(), percent);



    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

/*----------------------------------------------------------------------------*/

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