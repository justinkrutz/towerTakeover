#include "vex.h"
#include "driverControl.h"
#include "autonStructure.h"

using namespace vex;

timer LoopTime;
timer PrintTime;

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

int armsPos(armsPosDown);

bool trayMoving(false);
bool armsMoving(false);
bool intakeMoving(false);

bool turboTurn(false);

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

double stickForwardLast (0);
double stickForwardTemp (0);
double stickStrafeLast (0);
double stickStrafeTemp (0);
double stickTurnLast (0);
double stickTurnTemp (0);

bool overTemp (false);


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
    moveForward = moveForward * m;
    moveStrafe  = moveStrafe  * m;
    moveTurn    = moveTurn    * m;
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


int intakeSpin(double degrees, double percent)
{
  double pos = Intake.position(deg);
  autoIntake = percent;
  waitUntil(fabs(Intake.position(deg) - pos) > fabs(degrees));
  autoIntake = 0;

  return 0;
}


int intakeIn()
{
  if(autoIntake == 100) autoIntake = 0;
  else autoIntake = 100;

  return 0;
}

int intakeOut()
{
  if(autoIntake == -100) autoIntake = 0;
  else autoIntake = -100;

  return 0;
}

int intakeOutSlow()
{
  if(autoIntake == -60) autoIntake = 0;
  else autoIntake = -60;

  return 0;
}

/*===========================================================================*/


int goalIntake()
{
  double pos = Intake.position(deg);
  intakeMoving = true;
  if (LineTrackerTray.value(pct) > 70) {
  autoIntake = -30;
  waitUntil(LineTrackerTray.value(pct) < 50 || Intake.position(deg) < pos - 200);
  autoIntake = 0;
  }

  intakeMoving = false;
  return 0;
}

int goalDrive ()
{
  (task ( goalIntake ));

  // double time = Brain.Timer.time(msec);

  Drivetrain.resetRotation();
  Drivetrain.setStopping(brake);


  autoDrive = 30;
  waitUntil(LineTrackerLeft.reflectivity() > 20 || LineTrackerRight.reflectivity() > 20
  /*(Brain.Timer.time(msec) - time > 1200 && Competition.isAutonomous())*/);
  autoDrive = 0;
  wait(0.1, sec);

  strafeOutput = 0;

  autoDrive = -10;
  waitUntil(LineTrackerLeft.reflectivity() > 20 || LineTrackerRight.reflectivity() > 20
  /*(Brain.Timer.time(msec) - time > 900 && Competition.isAutonomous())*/);
  
  autoDrive = 0;
  Drivetrain.setStopping(coast);
  waitUntil(!intakeMoving);


  return 0;
}

int trayUpDrive ()
{
  waitUntil(Tray.position(deg) > 300);
  forwardFunction(1.5, 3, 5, 3, false);
  return 0;
}

int trayUp() {
  if(!trayMoving) {
    trayMoving = true;
    autoIntake = 0;
    (task ( trayUpDrive ));

    double tempTray;
    while (Tray.position(deg) < 730) {
      tempTray = ( Tray.position(deg) * -0.171 + 120 );
      if (Tray.position(deg) > 620) {
        tempTray = ( Tray.position(deg) * 0.3 - 172 );
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
  }

  return 0;
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
  return 0;
}


int trayDown()
{
  if( trayMoving) {
    wait(1, sec);
  }
  if( !trayMoving) {
    trayMoving = true;
    autoIntake = 0;
    (task ( trayDownDrive ));
    while (Tray.position(deg) > 0){
      autoTray = ( ( Tray.position(deg) * -0.32 -50));
      vex::task::sleep(20);
    }
    autoTray = 0;
    trayMoving = false;
  }

  return 0;
}

int trayStart ()
{
  if (Tray.position(deg) > 25){
    trayDown();
  } else {
  goalDrive();
  trayUp();
  trayDown();
  }

  return 0;
}

int trayStop ()
{
  task::stop( goalDrive );
  task::stop( trayUp );
  if (!(autoTray < 0)) {
  autoArms = 0;
  autoDrive = 0;
  autoIntake = 0;
  autoTray = 0;
  trayMoving = false;
  }
  return 0;
}




/*===========================================================================*/

int armsMove (double degrees, double percent, vex::brakeType brakeType)
{
  autoArms = percent;
  if (percent > 0) waitUntil(fabs(Arms.position(deg)) >= fabs(degrees * 5));
  else if (percent < 0) waitUntil(fabs(Arms.position(deg)) <= fabs(degrees * 5));
  autoArms = 0;
  Arms.setStopping(brakeType);

  return 0;
}

int armsDown ()
{
  if(!armsMoving) {
    armsMoving = true;
    while (Arms.position(deg) > 0)
    {
      autoArms = ( ( Arms.position(deg) * -0.25 - 10 ));
      vex::task::sleep(20);
    }
    autoArms = 0;
    armsMoving = false;
  // Arms.setStopping(brake);
  armsPos = armsPosDown;
  }

  return 0;
}

int armsHigh ()
{
  if(!armsMoving) {
    if(!(armsPos == armsPosHigh)) {
      autoArms = 0;
      armsPos = armsPosHigh;
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(250, -100);
      while (Arms.position(deg) < 850) 
      {
        autoArms = ( Arms.position(deg) * -0.25 + 222.5 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
    } else {
      autoArms = 0;
      intakeSpin(100, -100);
      autoArms = -100;
      intakeSpin(360, -100);
      waitUntil(Arms.position(deg) < 600);
      autoArms = 0;
      armsDown();
    }
  }

  return 0;
}

int armsLow ()
{
  if(!armsMoving) { // are the Arms moving?
    if(armsPos == armsPosDown) {
      autoArms = 0;
      armsPos = armsPosLow;
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(230, -100);
      while (Arms.position(deg) < 600) {
        autoArms = ( Arms.position(deg) * -0.25 + 160 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
    } else {
      autoArms = 0;
      intakeSpin(360, -100);
      forwardFunction(-4, 50, 50, 5, false);
      armsDown();
    }
  }

  return 0;
}

/*===========================================================================*/



int greenToggleButton ()
{
  greenToggle = !greenToggle;

  return 0;
}

int purpleToggleButton ()
{
  purpleToggle = !purpleToggle;

  return 0;
}

int orangeToggleButton ()
{
  orangeToggle = !orangeToggle;

  return 0;
}





int visionDetectFunction (bool turn, double turnP, double time)
{
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
  
  while (Controller1.ButtonL2.pressing() || Controller1.ButtonL1.pressing()
  || (Brain.Timer.time(msec) - oldTime < time && time != 0)) {

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

  return 0;
}

int visionTurnFunction ()
{
  visionDetectFunction(true);

  return 0;
}

int visionStrafeFunction ()
{
  visionDetectFunction(false);

  return 0;
}

int trayReset ()
{
  Tray.resetPosition();

  return 0;
}

int armsReset ()
{
  Arms.resetPosition();

  return 0;
}

int driveSlow()
{
  if(driveSpeed == 0.5) driveSpeed = 1;
  else driveSpeed = 0.5;

  return 0;
}

int abortEverything()
{
  task::stop( trayUp );
  task::stop( trayStart );
  task::stop( trayStop );
  task::stop( intakeIn );
  task::stop( intakeOutSlow );
  task::stop( driveSlow );
  task::stop( armsHigh );
  task::stop( armsLow );
  task::stop( intakeOut );
  task::stop( orangeToggleButton );
  task::stop( purpleToggleButton );
  task::stop( greenToggleButton );
  task::stop( goalDrive );
  task::stop( trayUp );
  task::stop( trayDown );
  task::stop( trayReset );
  task::stop( armsReset );
  task::stop( goalDrive );
  task::stop( trayUpDrive );
  task::stop( trayDownDrive );

  autoArms = 0;
  autoDrive = 0;
  autoIntake = 0;
  autoTray = 0;
  autoTurn = 0;
  forwardOutput = 0;
  strafeOutput = 0;
  visionStrafe = 0;
  turnOutput = 0;
  visionTurn = 0;

  armsMoving = false;
  trayMoving = false;
  intakeMoving = false;

  armsPos = armsPosLow;


  return 0;
}












int setButtonCallbacks()
{
  Controller1.ButtonY.     pressed (setFunction( trayUp ));
  Controller1.ButtonX.     pressed (setFunction( trayStart ));
  Controller1.ButtonX.    released (setFunction( trayStop ));
  Controller1.ButtonY.    released (setFunction( trayStop ));
  Controller1.ButtonB.     pressed (setFunction( abortEverything ));

  Controller1.ButtonR2.    pressed (setFunction( intakeIn ));
  Controller1.ButtonR1.    pressed (setFunction( intakeOutSlow ));

  Controller1.ButtonL2.    pressed (setFunction( driveSlow ));

  Controller1.ButtonUp.    pressed (setFunction( armsHigh ));
  Controller1.ButtonDown.  pressed (setFunction( armsLow ));
  Controller1.ButtonRight. pressed (setFunction( intakeOut ));


  Controller2.ButtonLeft.  pressed (setFunction( orangeToggleButton ));
  Controller2.ButtonUp.    pressed (setFunction( purpleToggleButton ));
  Controller2.ButtonRight. pressed (setFunction( greenToggleButton ));

  Controller2.ButtonY.     pressed (setFunction( goalDrive ));
  Controller2.ButtonX.     pressed (setFunction( trayUp ));
  Controller2.ButtonA.     pressed (setFunction( trayDown ));

  Controller2.ButtonR1.    pressed (setFunction( trayReset ));
  Controller2.ButtonL1.    pressed (setFunction( armsReset ));

  return 0;
}

void unassign() {}

void drivetrainControl()
{
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
}

void manualControl()
{
  if (Controller1.ButtonA.pressing() && Tray.position(deg) > 0){
    trayButton = -30;
  } else {
    trayButton = 0;
  }


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
}

void controllerInfo()
{
  if (IntakeLeft.torque() > 1.05 || IntakeRight.torque() > 1.05)
  {
    Controller1.rumble(".");
    Controller2.rumble(".");

  }

  if(
    !overTemp &&
    (int(FrontLeftDrive.temperature() * 0.1) >= 7 ||
    int(FrontRightDrive.temperature() * 0.1) >= 7 ||
    int(BackLeftDrive.temperature() * 0.1) >= 7 ||
    int(BackRightDrive.temperature() * 0.1) >= 7 ||
    int(IntakeLeft.temperature() * 0.1) >= 7 ||
    int(IntakeRight.temperature() * 0.1) >= 7 ||
    int(Tray.temperature() * 0.1) >= 7 ||
    int(Arms.temperature() * 0.1) >= 7)
    )
  {
      Controller1.rumble("...---...   ...---...");
      Controller2.rumble("...---...   ...---...");
      overTemp = true;
  }

  if(PrintTime.time(msec) >= 15) {
    Controller1.Screen.setCursor(1, 1);
    // Controller1.Screen.clearLine();
    Controller1.Screen.print("FL%d, FR%d, BL%d, BR%d", int(FrontLeftDrive.temperature() * 0.1), int(FrontRightDrive.temperature() * 0.1), int(BackLeftDrive.temperature() * 0.1), int(BackRightDrive.temperature() * 0.1));
    Controller1.Screen.setCursor(2, 1);
    // Controller1.Screen.clearLine();
    Controller1.Screen.print("IL%d, IR%d, T%d, A%d", int(IntakeLeft.temperature() * 0.1), int(IntakeRight.temperature() * 0.1), int(Tray.temperature() * 0.1), int(Arms.temperature() * 0.1));
    Controller1.Screen.setCursor(3, 1);
    // Controller1.Screen.clearLine();
    Controller1.Screen.print("L%d, R%d, T%d, I%f", LineTrackerLeft.reflectivity(), LineTrackerRight.reflectivity(), LineTrackerTray.reflectivity(), gyroYaw);
    PrintTime.reset();
  }
}