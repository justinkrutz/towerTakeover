#include "vex.h"

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
vex::timer loopTime;
motor_group intake ( intakeLeft, intakeRight );

// vision::signature CUBE_ORANGE (1, 6343, 7765, 7054, -2843, -1635, -2239, 3.000, 0);
// vision::signature CUBE_GREEN (2, -6065, -3709, -4887, -3385, -1461, -2423, 2.500, 0);
// vision::signature CUBE_PURPLE (3, 1401, 2161, 1781, 7625, 9415, 8520, 3.000, 0);
// vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vex::vision vision1 ( vex::PORT1, 60, CUBE_ORANGE, CUBE_GREEN, CUBE_PURPLE, SIG_4, SIG_5, SIG_6, SIG_7 );

double stickForward(0);
double stickSideways(0);
double stickTurn(0);

double autoTray(0);
double autoDrive(0);
double autoTurn(0);
double autoIntake(0);

double buttonIntake(0);

double rampDrive(0);

double rampTurn(0);

double lastTime(0);

int intakeJammed(1);

bool trayMoving(false);

bool turboTurn(false);

bool autoAbort(false);


/*===========================================================================*/

void turboTurnButton()
{
  turboTurn = !turboTurn;
}

void intakeFwd()
{
  if(intake.velocity(pct) > 80) buttonIntake = 0;
  else buttonIntake = 100;
}

void intakeRev()
{
  if(intake.velocity(pct) < -1) buttonIntake = 0;
  else buttonIntake = -20;
}

void intakeFwdSlow()
{
  if(intake.velocity(pct) > 1 && intake.velocity(pct) < 80) buttonIntake = 0;
  else buttonIntake = 20;
}

void trayUp()
  {
    if(!trayMoving) {
      trayMoving = true;
      while (tray.position(deg) < 300 && !autoAbort) 
      {
        autoTray = ( tray.position(deg) * -0.1 + 100 );
        vex::task::sleep(20);
      }
      while (tray.position(deg) < 750) 
      {
        autoTray = ( tray.position(deg) * -0.1 + 100 );
        autoIntake = 50;
        vex::task::sleep(20);
      }
    autoTray = 0;
    autoIntake = 0;
    trayMoving = false;
  }
}

void trayDown()
{
  if(!trayMoving) {
    trayMoving = true;
    while (tray.position(deg) > 0 && !autoAbort) 
    {
      autoTray = ( ( tray.position(deg) * -0.07 + 100 ) * -1);
      vex::task::sleep(20);
    }
      autoIntake = -50;
      autoDrive = -25;
          vex::task::sleep(400);
    
    autoTray = 0;
    autoIntake = 0;
    autoDrive = 0;
    trayMoving = false;
  }
}


/*===========================================================================*/

void pre_auton( void ) {
  // Inertial.calibrate();
  menuLcdDraw();
  controllerDraw();
  tray.setStopping(brake);
  tray.setTimeout(3, seconds);
  tray.setPosition(-66, deg);

  Controller1.ButtonX.pressed(trayUp);
  Controller1.ButtonA.pressed(trayDown);
  Controller1.ButtonR2.pressed(intakeFwd);
  Controller1.ButtonR1.pressed(intakeRev);
  Controller1.ButtonY.pressed(intakeFwdSlow);
  Controller1.ButtonDown.pressed(turboTurnButton);


  // Drivetrain.setTimeout(3, seconds);
  tray.setTimeout(3, seconds);
  tray.setTimeout(3, seconds);

  intake.setStopping(hold);

  while (!Competition.isAutonomous() || !Competition.isEnabled()) {
    menuLcdTouch();
    vex::task::sleep(20);
  }
}

/*===========================================================================*/

void autonomous( void ) {
  vex::task::sleep(200);
  autonIndicator();
  // Drivetrain.driveFor(reverse, 2, inches, 50, rpm);
  tray.spinToPosition(100, deg, 100, rpm);
  tray.spinToPosition(0, deg, 100, rpm);
  // intake.rotateFor(2, rev, 200, rpm);
  vex::task::sleep(500); 
  // Drivetrain.driveFor(fwd, 22, inches, 50, rpm);
  // Drivetrain.driveFor(reverse, 5, inches, 50, rpm);
  vex::task::sleep(3000);
  return;
}

/*===========================================================================*/

void usercontrol( void ) {
  // Brain.loopTimer.
  loopTime.reset();

  while (1) {

    // if (Controller1.ButtonL1.pressing()) {
    //   axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000 * 0.25);
    //   axis1Prop = (pow(Controller1.Axis1.position(), 3) / 10000 * 0.25);
    // } else if (Controller1.ButtonL2.pressing()) {
    //   axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000 * 0.5);
    //   axis1Prop = (pow(Controller1.Axis1.position(), 3) / 10000 * 0.5);
    // } else {
    //   axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000);
    //   axis1Prop = (pow(Controller1.Axis1.position(), 3) / 10000);
    //   // axis3Prop = (Controller1.Axis3.position());
    //   // axis1Prop = (Controller1.Axis1.position());
    // }
    // axis3Prop = (pow(Controller1.Axis3.position(), 3) / 10000);

    // if (turboTurn) Drivetrain.arcade(axis3Prop + autoDrive, axis1Prop);
    // else Drivetrain.arcade(axis3Prop + autoDrive, axis1Prop* 0.25);

    // if (axis3Prop + autoDrive > Drivetrain.velocity(pct) + 20) {
    //   rampDrive = rampDrive + loopTime.time()/5;
    // } else if (axis3Prop + autoDrive < Drivetrain.velocity(pct) - 20) {
    //   rampDrive = rampDrive - loopTime.time()/5;
    // } else if (axis3Prop + autoDrive <= Drivetrain.velocity(pct) + 20 && axis3Prop + autoDrive >= Drivetrain.velocity(pct) - 20) {
    //   rampDrive = axis3Prop + autoDrive;
    // }

    // if (Controller1.ButtonUp.pressing()) 
    // {
    //   autoTurn = vision1.largestObject.centerX;
    // }



    // loopTime.reset();

    if(leftIntakeSwitch.pressing() && rightIntakeSwitch.pressing() ){
      intakeJammed = 1;
    } else {
      intakeJammed = -1;
    }


    stickForward = Controller1.Axis2.position();
    stickSideways = Controller1.Axis1.position();
    stickTurn = Controller1.Axis4.position() * (Controller1.Axis3.position() + 120) / 200;



    frontRight.spin(fwd, stickForward - stickSideways - stickTurn, pct);
    frontLeft.spin(fwd,  stickForward + stickSideways + stickTurn, pct);
    backRight.spin(fwd,  stickForward + stickSideways - stickTurn, pct);
    backLeft.spin(fwd,   stickForward - stickSideways + stickTurn, pct);

    intakeLeft.spin(fwd, (Controller2.Axis3.position() + Controller2.Axis4.position() + buttonIntake + autoIntake) * intakeJammed, percent);
    intakeRight.spin(fwd, (Controller2.Axis3.position() - Controller2.Axis4.position() + buttonIntake + autoIntake), percent);

    tray.spin(fwd, Controller2.Axis2.position() + autoTray, percent);

    if (intakeLeft.torque() > 1.05 || intakeRight.torque() > 1.05)
    {
      Controller1.rumble(".");
      Controller2.rumble(".");

    }

    autoAbort = Controller1.ButtonRight.pressing();

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(Controller1.Axis3.position());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(Controller1.Axis4.position());
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(goalButton.pressing());
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