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

using namespace vex;
competition Competition;
timer LoopTime;
timer PrintTime;
motor_group intake ( IntakeLeft, IntakeRight );
motor_group Drivetrain ( FrontLeftDrive, FrontRightDrive, BackLeftDrive, BackRightDrive );

// vision::signature CUBE_ORANGE (1, 6343, 7765, 7054, -2843, -1635, -2239, 3.000, 0);
// vision::signature CUBE_GREEN (2, -6065, -3709, -4887, -3385, -1461, -2423, 2.500, 0);
// vision::signature CUBE_PURPLE (3, 1401, 2161, 1781, 7625, 9415, 8520, 3.000, 0);
// vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
// vex::vision vision1 ( vex::PORT1, 60, CUBE_ORANGE, CUBE_GREEN, CUBE_PURPLE, SIG_4, SIG_5, SIG_6, SIG_7 );

#define down 0
#define low 1
#define high 2

#define cubeGreen FrontVision__SIG_1
#define cubeOrange FrontVision__SIG_2
#define cubePurple FrontVision__SIG_3

double stickForward(0);
double stickStrafe(0);
double stickTurn(0);

double autoTray(0);
double autoArms(0);
double autoDrive(0);
double autoTurn(0);
double autoIntake(0);

double rampDrive(0);

double rampTurn(0);

double visionTurn(0);
double visionStrafe(0);

double lastTime(0);

int armsPos(down);

bool trayMoving(false);
bool armsMoving(false);
bool intakeMoving(false);

bool turboTurn(false);

bool autoAbort(false);

bool autoAbortTray(false);

bool greenToggle(true);
bool orangeToggle(true);
bool purpleToggle(true);
bool Button(true);

double trayStick (0);
double trayButton (0);
double intakeStick (0);
double intakeStickTwist (0);

double armsStick (0);

double driveSpeed(1);


/*===========================================================================*/

int motorTask()
{
  double moveForward;
  double moveStrafe;
  double moveTurn;
  double m;
  while(1)
  {
  moveForward = ( forwardOutput + stickForward + autoDrive );
  moveStrafe  = ( strafeOutput + stickStrafe + visionStrafe ) * strafeSpeedP;
  moveTurn    = ( turnOutput    + stickTurn + visionTurn );

  if(fabs(moveForward) + fabs(moveStrafe) + fabs(moveTurn) > 100) {
    m = 100 / (fabs(moveForward) + fabs(moveStrafe) + fabs(moveTurn));
    moveForward = moveForward * /* sign(moveForward) * */ m;
    moveStrafe  = moveStrafe  * /* sign(moveStrafe)  * */ m;
    moveTurn    = moveTurn    * /* sign(moveTurn)    * */ m;
  }

  FrontRightDrive.spin (fwd,moveForward - moveStrafe - moveTurn, pct);
  FrontLeftDrive.spin  (fwd,moveForward + moveStrafe + moveTurn, pct);
  BackRightDrive.spin  (fwd,moveForward + moveStrafe - moveTurn, pct);
  BackLeftDrive.spin   (fwd,moveForward - moveStrafe + moveTurn, pct);

  IntakeLeft.spin  (fwd, (intakeStick + intakeStickTwist + autoIntake), percent);
  IntakeRight.spin (fwd, (intakeStick - intakeStickTwist + autoIntake), percent);
  Arms.spin(fwd, armsStick + autoArms, pct);
  Tray.spin(fwd, autoTray + trayStick + trayButton, percent);
  task::sleep(5);
  }
  
  return(0);
}


/*===========================================================================*/


void intakeSpin(double degrees, double percent)
{
  double pos = intake.position(deg);
  autoIntake = percent;
  waitUntil(autoAbort || fabs(intake.position(deg) - pos) > fabs(degrees));
  autoIntake = 0;
}


void intakeIn()
{
  if(autoIntake == 100) autoIntake = 0;
  else autoIntake = 100;
}

void intakeOut()
{
  if(autoIntake == -100) autoIntake = 0;
  else autoIntake = -100;
}

void trayLow()
{
  
}

void intakeOutSlow()
{
  if(autoIntake == -60) autoIntake = 0;
  else autoIntake = -60;

}

/*===========================================================================*/


int goalIntake()
{
  double pos = intake.position(deg);
  intakeMoving = true;
  if (LineTrackerTray.value(pct) > 70 && !autoAbort) {
  autoIntake = -30;
  waitUntil(autoAbort || LineTrackerTray.value(pct) < 50 || intake.position(deg) < pos - 200);
  autoIntake = 0;
  }

  intakeMoving = false;
  return 0;
}

void goalDrive ()
{
  task task5 = task( goalIntake );

  // double time = Brain.Timer.time(msec);

  Drivetrain.resetRotation();
  Drivetrain.setStopping(brake);
        printf("%f Time goalDrive Start\n", Brain.Timer.time(msec));
        printf("%ld LineTrackerRight Start\n", LineTrackerRight.reflectivity());


  autoDrive = 30;
  waitUntil(autoAbort || LineTrackerLeft.reflectivity() > 20 || LineTrackerRight.reflectivity() > 20 /*(Brain.Timer.time(msec) - time > 1200 && Competition.isAutonomous())*/);
        printf("%f Time goalDrive mid\n", Brain.Timer.time(msec));
        printf("%ld LineTrackerRight mid\n", LineTrackerRight.reflectivity());
  autoDrive = 0;
  wait(0.1, sec);

  strafeOutput = 0;

  autoDrive = -10;
  waitUntil(autoAbort || LineTrackerLeft.reflectivity() > 20 || LineTrackerRight.reflectivity() > 20 /*(Brain.Timer.time(msec) - time > 900 && Competition.isAutonomous())*/);
        printf("%f Time goalDrive end\n", Brain.Timer.time(msec));
        printf("%ld LineTrackerRight end\n", LineTrackerRight.reflectivity());
  
  autoDrive = 0;
  Drivetrain.setStopping(coast);
  waitUntil(autoAbort || !intakeMoving);
}

int trayUpDrive ()
{
  waitUntil(autoAbort || Tray.position(deg) > 300);
  forwardFunction(1.5, 3, 5, 3, false);
  return 0;
}

void trayUp() {
  if(!trayMoving) {
    printf("trayUp start\n");
    printf("%f trayUp pos\n", Tray.position(deg));
    trayMoving = true;
    autoIntake = 0;
    task trayUpDriveTask ( trayUpDrive );

    double tempTray;
    while (Tray.position(deg) < 730 && !autoAbort) {
      tempTray = ( Tray.position(deg) * -0.171 + 120 );
      if (Tray.position(deg) > 620) {
        tempTray = ( Tray.position(deg) * 0.3 - 172 );
        printf("trayUp mid\n");
      } else if (Tray.position(deg) > 300) {
        Arms.setStopping(coast);
      } else {
        Arms.setStopping(hold);
      }
      autoTray = tempTray;
      vex::task::sleep(5);
    }
    autoTray = 0;
    autoIntake = 0;
    autoDrive = 0;
    trayMoving = false;
    printf("trayUp end\n");
  }
}

int trayDownDrive()
{
    Arms.setStopping(hold);
    forwardFunction(-6, 25, 25, 5, false);
    wait(0.1, sec);
    intakeSpin(360, -100);
    while(Arms.position(deg) < 0) {
      autoArms = 5;
      vex::task::sleep(5);
    }
      autoArms = 0;
    printf("%f Time after trayDown\n", Brain.Timer.time(msec));
    printf("%f InchesF after trayDown\n", forwardDistance);
  return 0;
}


void trayDown()
{
  if(!autoAbort && trayMoving) {
    wait(1, sec);
  }
  if(!autoAbort && !trayMoving) {
    trayMoving = true;
    autoIntake = 0;
    task trayDownDriveTask = task( trayDownDrive );
    while (Tray.position(deg) > 0 && !autoAbort){
      autoTray = ( ( Tray.position(deg) * -0.32 -50));
      vex::task::sleep(20);
    }
    autoTray = 0;
    trayMoving = false;
  }
}

void trayStart ()
{
  autoAbortTray = false;
  if (Tray.position(deg) > 25){
    trayDown();
  } else {
  goalDrive();
  trayUp();
  trayDown();
  }
}

void trayStop ()
{
  autoAbortTray = true;
  wait(0.3, sec);
  autoAbortTray = false;
}




/*===========================================================================*/

void armsMove (double degrees, double percent, vex::brakeType brakeType)
{
  autoArms = percent;
  if (percent > 0) waitUntil(autoAbort || fabs(Arms.position(deg)) >= fabs(degrees * 5));
  else if (percent < 0) waitUntil(autoAbort || fabs(Arms.position(deg)) <= fabs(degrees * 5));
  autoArms = 0;
  Arms.setStopping(brakeType);
}

void armsDown ()
{
  if(!armsMoving) {
    armsMoving = true;
    while (Arms.position(deg) > 0 && !autoAbort)
    {
      autoArms = ( ( Arms.position(deg) * -0.25 - 10 ));
      vex::task::sleep(20);
    }
    autoArms = 0;
    armsMoving = false;
  // Arms.setStopping(brake);
  armsPos = down;
  }
}

void armsHigh ()
{
  if(!armsMoving) {
    if(!(armsPos == high)) {
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(250, -100);
      while (Arms.position(deg) < 850 && !autoAbort) 
      {
        autoArms = ( Arms.position(deg) * -0.25 + 222.5 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
      // Arms.setStopping(hold);
      armsPos = high;
    } else {
      intakeSpin(100, -100);
      autoArms = -100;
      intakeSpin(360, -100);
      waitUntil(autoAbort || Arms.position(deg) < 600);
      autoArms = 0;
      armsDown();
    }
  }
}

void armsLow ()
{
  if(!armsMoving) { // are the Arms moving?
    if(armsPos == down) {
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(230, -100);
      while (Arms.position(deg) < 600 && !autoAbort) {
        autoArms = ( Arms.position(deg) * -0.25 + 160 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
      // Arms.setStopping(hold);
      armsPos = low;
    } else {
      intakeSpin(360, -100);
      forwardFunction(-4, 50, 50, 5, false);
      armsDown();
    }
  }
}

/*===========================================================================*/



void greenToggleButton ()
{
  greenToggle = !greenToggle;
}

void purpleToggleButton ()
{
  purpleToggle = !purpleToggle;
}

void orangeToggleButton ()
{
  orangeToggle = !orangeToggle;
}





void visionDetectFunction (bool turn, double turnP, double time)
{
          printf("%f Time vision start\n", Brain.Timer.time(msec));
  double posOrange;
  double posPurple;
  double posGreen;

  double heightOrange;
  double heightPurple;
  double heightGreen;

  double tempSteer;
  double tempHeight;

  double objectCount;

  double oldTime = Brain.Timer.time(msec);

  vex::timer intakeTime;
  Flashlight.on();
  
  while (Controller1.ButtonL2.pressing() || Controller1.ButtonL1.pressing() || (Brain.Timer.time(msec) - oldTime < time && time != 0)) {
          printf("%f Time vision while\n", Brain.Timer.time(msec));

    Controller2.Screen.clearScreen();
    
    FrontVision.takeSnapshot(cubeOrange);
    objectCount = FrontVision.objectCount;
    posOrange = (FrontVision.largestObject.centerX - 165) * orangeToggle;
    heightOrange = FrontVision.largestObject.height;


    FrontVision.takeSnapshot(cubePurple);
    objectCount = objectCount + FrontVision.objectCount;
    posPurple = (FrontVision.largestObject.centerX - 165) * purpleToggle;
    heightPurple = FrontVision.largestObject.height;

    FrontVision.takeSnapshot(cubeGreen);
    objectCount = objectCount + FrontVision.objectCount;
    posGreen = (FrontVision.largestObject.centerX - 165) * greenToggle;
    heightGreen = FrontVision.largestObject.height;

    Controller2.Screen.setCursor(1, 1);
    Controller2.Screen.print("Green H %d", FrontVision.largestObject.height);
    Controller2.Screen.setCursor(2, 1);
    Controller2.Screen.print("Green X %d", FrontVision.largestObject.centerX - 165);


    tempSteer = posOrange;
    tempHeight = heightOrange;

    if (heightPurple > tempHeight) {
      tempSteer = posPurple;
      tempHeight = heightPurple;
    }

    if (heightGreen > tempHeight) {
      tempSteer = posGreen;
      tempHeight = heightGreen;
    }


    if (objectCount > 0 && tempHeight > 20) {
      if (turn) {
      visionStrafe = 0;
      visionTurn = tempSteer * 0.5;
      } else {
      visionTurn = 0;
      visionStrafe = tempSteer;
      }
    } else {
      visionTurn = 0;
      visionStrafe = 0;
    }

    if (objectCount > 0 && tempHeight > 80) {
      autoIntake = 100;
      intakeTime.clear();
    } else if (intakeTime.time(sec) > 2) {
      autoIntake = 0;
    }
  }
  visionTurn = 0;
  visionStrafe = 0;
  autoIntake = 0;
  Flashlight.off();
          printf("%f Time vision end\n", Brain.Timer.time(msec));
}

void visionTurnFunction ()
{
  visionDetectFunction(true);
}

void visionStrafeFunction ()
{
  visionDetectFunction(false);
}

void trayReset ()
{
  Tray.resetPosition();
}

void armsReset ()
{
  Arms.resetPosition();
}

void driveSlow()
{
  if(driveSpeed == 0.5) driveSpeed = 1;
  else driveSpeed = 0.5;
}













void unassign()
{

}

void tipWheelTrigger()
{
  printf("%f Time tipWheel\n", Brain.Timer.time(msec));
}


/*===========================================================================*/

void pre_auton( void ) {
  Flashlight.off();
  Inertial.calibrate();
  menuLcdDraw();
  controllerDraw();
  Tray.setStopping(hold);
  Tray.setTimeout(1, seconds);

  TipWheel.released(tipWheelTrigger);

  Brain.Screen.pressed(menuLcdTouch);

  Controller1.ButtonY.pressed(trayUp);
  Controller1.ButtonX.pressed(trayStart);
  Controller1.ButtonX.released(trayStop);

  Controller1.ButtonR2.pressed(intakeIn);
  Controller1.ButtonR1.pressed(intakeOutSlow);

  // Controller1.ButtonL2.pressed(visionTurnFunction);
  // Controller1.ButtonL1.pressed(visionStrafeFunction);

  Controller1.ButtonL2.pressed(driveSlow);

  Controller1.ButtonUp.pressed(armsHigh);
  Controller1.ButtonDown.pressed(armsLow);
  Controller1.ButtonLeft.pressed(trayLow);
  Controller1.ButtonRight.pressed(intakeOut);




  Controller2.ButtonLeft.pressed(orangeToggleButton);
  Controller2.ButtonUp.pressed(purpleToggleButton);
  Controller2.ButtonRight.pressed(greenToggleButton);

  Controller2.ButtonY.pressed(goalDrive);
  Controller2.ButtonX.pressed(trayUp);
  Controller2.ButtonA.pressed(trayDown);

  Controller2.ButtonR1.pressed(trayReset);
  Controller2.ButtonL1.pressed(armsReset);




  // Drivetrain.setTimeout(3, seconds);
  Arms.setTimeout(1, seconds);
  Arms.setStopping(hold);

  intake.setTimeout(1, seconds);
  intake.setStopping(hold);



  Inertial.calibrate();

  task task1 = task( motorTask );
  autonTaskStart();


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
  vex::task::sleep(5);
  }
  autoArms = 0;

  printf("%f Degrees drive\n", gyroYaw);
  printf("%f Degrees Arms\n", Arms.position(deg));

  double stickForwardLast (0);
  double stickForwardTemp (0);
  double stickStrafeLast (0);
  double stickStrafeTemp (0);
  double stickTurnLast (0);
  double stickTurnTemp (0);

  bool overTemp (false);
  while (1) {
    stickForwardTemp = Controller1.Axis2.position() * driveSpeed;
    stickStrafeTemp = Controller1.Axis1.position() * driveSpeed;
    stickTurnTemp = Controller1.Axis4.position() * ((Controller1.Axis3.position() + 150) * 0.005) * driveSpeed;

    if(stickForwardTemp > stickForwardLast + LoopTime * 0.2) {
      stickForwardTemp = stickForwardLast + LoopTime * 0.2;
    } else if(stickForwardTemp < stickForwardLast - LoopTime * 0.2) {
      stickForwardTemp = stickForwardLast - LoopTime * 0.2;
    }

    if(stickStrafeTemp > stickStrafeLast + LoopTime * 0.2) {
      stickStrafeTemp = stickStrafeLast + LoopTime * 0.2;
    } else if(stickStrafeTemp < stickStrafeLast - LoopTime * 0.2) {
      stickStrafeTemp = stickStrafeLast - LoopTime * 0.2;
    }

    if(stickTurnTemp > stickTurnLast + LoopTime * 0.2) {
      stickTurnTemp = stickTurnLast + LoopTime * 0.2;
    } else if(stickTurnTemp < stickTurnLast - LoopTime * 0.2) {
      stickTurnTemp = stickTurnLast - LoopTime * 0.2;
    }

    stickForwardLast = stickForwardTemp;
    stickStrafeLast = stickStrafeTemp;
    stickTurnLast = stickTurnTemp;
    LoopTime.reset();

    stickForward = stickForwardTemp;
    stickStrafe = stickStrafeTemp;
    stickTurn = stickTurnTemp;


    if(Controller2.Axis2.position() < - 5 || Controller2.Axis2.position() > 10)
    {
      if(Controller2.ButtonR2.pressing()) 
      {
        trayStick = 0;
        intakeStick = -Controller2.Axis2.position();
        intakeStickTwist = Controller2.Axis1.position();
      } else {
        intakeStick = 0;
        intakeStickTwist = 0;
        trayStick = Controller2.Axis2.position();
      }
    } else {
      trayStick = 0;
      intakeStick = 0;
    }

    armsStick = Controller2.Axis3.position();


    if (IntakeLeft.torque() > 1.05 || IntakeRight.torque() > 1.05)
    {
      Controller1.rumble(".");
      Controller2.rumble(".");

    }

    autoAbort = Controller1.ButtonB.pressing() || Controller2.ButtonB.pressing() || autoAbortTray;

    if (Controller1.ButtonA.pressing()){
      trayButton = -30;
    } else {
      trayButton = 0;
    }

    if(!overTemp &&
      (int(FrontLeftDrive.temperature() * 0.1) >= 7 ||
       int(FrontRightDrive.temperature() * 0.1) >= 7 ||
       int(BackLeftDrive.temperature() * 0.1) >= 7 ||
       int(BackRightDrive.temperature() * 0.1) >= 7 ||
       int(IntakeLeft.temperature() * 0.1) >= 7 ||
       int(IntakeRight.temperature() * 0.1) >= 7 ||
       int(Tray.temperature() * 0.1) >= 7 ||
       int(Arms.temperature() * 0.1) >= 7))
      {
        Controller1.rumble("...---...");
        Controller2.rumble("...---...");
        overTemp = true;
      }

    if(PrintTime.time(msec) >= 15) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("FL%d, FR%d, BL%d, BR%d", int(FrontLeftDrive.temperature() * 0.1), int(FrontRightDrive.temperature() * 0.1), int(BackLeftDrive.temperature() * 0.1), int(BackRightDrive.temperature() * 0.1));
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("IL%d, IR%d, T%d, A%d", int(IntakeLeft.temperature() * 0.1), int(IntakeRight.temperature() * 0.1), int(Tray.temperature() * 0.1), int(Arms.temperature() * 0.1));
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("L%d, R%d, T%d, I%f", LineTrackerLeft.reflectivity(), LineTrackerRight.reflectivity(), LineTrackerTray.reflectivity(), gyroYaw);
    PrintTime.reset();
    }
    vex::task::sleep(5); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

/*===========================================================================*/

int main() {
  vexcodeInit();
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  
  //Run the pre-autonomous function. 
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(1) {
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }    
       
}