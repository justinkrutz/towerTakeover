// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// intakeLeft           motor         12              
// intakeRight          motor         13              
// Controller2          controller                    
// tray                 motor         21              
// arms                 motor         14              
// Inertial             inertial      2               
// backLeft             motor         7               
// frontLeft            motor         8               
// backRight            motor         9               
// frontRight           motor         10              
// Vision               vision        15              
// LineTrackerRight     line          A               
// LineTrackerLeft      line          B               
// LineTrackerTray      line          C               
// tipWheel             bumper        D               
// Flashlight           led           H               
// ---- END VEXCODE CONFIGURED DEVICES ----



#include "vex.h"

using namespace vex;
vex::competition Competition;
vex::timer loopTime;
motor_group intake ( intakeLeft, intakeRight );
motor_group Drivetrain ( frontLeft, frontRight, backLeft, backRight );

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

#define cubeGreen Vision__SIG_1
#define cubeOrange Vision__SIG_2
#define cubePurple Vision__SIG_3

double forwardDistanceP(28.647889757);
double strafeDistanceP(32.243767313);
double strafeSpeedP(1.12551980572);

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

double armsStick (0);


/*===========================================================================*/

int motorTask()
{
  while(1)
  {
  double moveForward = forwardOutput + stickForward + autoDrive;
  double moveStrafe  = strafeOutput  + stickStrafe + visionStrafe;
  double moveTurn    = turnOutput    + stickTurn + visionTurn;

  frontRight.spin(fwd, moveForward - moveStrafe - moveTurn, pct);
  frontLeft.spin(fwd,  moveForward + moveStrafe + moveTurn, pct);
  backRight.spin(fwd,  moveForward + moveStrafe - moveTurn, pct);
  backLeft.spin(fwd,   moveForward - moveStrafe + moveTurn, pct);

  intakeLeft.spin(fwd, (-Controller2.Axis3.position() - Controller2.Axis4.position() + autoIntake), percent);
  intakeRight.spin(fwd, (-Controller2.Axis3.position() + Controller2.Axis4.position() + autoIntake), percent);
  arms.spin(fwd, armsStick + autoArms, pct);
  tray.spin(fwd, autoTray + trayStick + trayButton, percent);
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

void intakeInSlow()
{
  if(autoIntake == 20) autoIntake = 0;
  else autoIntake = 20;
}

void intakeOutSlow()
{
  if(autoIntake == -20) autoIntake = 0;
  else autoIntake = -20;

}

/*===========================================================================*/


int goalIntake()
{
  double pos = intake.position(deg);
  intakeMoving = true;
  if (LineTrackerTray.value(pct) > 70 && !autoAbort) {
  autoIntake = -20;
  waitUntil(autoAbort || LineTrackerTray.value(pct) < 50 || intake.position(deg) < pos - 270);
  autoIntake = 0;
  // intakeSpin(30, -20);
  }

  intakeMoving = false;
  return 0;
}

void goalDrive ()
{
  task task5 = task( goalIntake );

  Drivetrain.resetRotation();
  Drivetrain.setStopping(brake);


  autoDrive = 30;
  waitUntil(autoAbort || LineTrackerLeft.reflectivity() > 40 || LineTrackerRight.reflectivity() > 40);
  autoDrive = 0;
  wait(0.1, sec);

  autoDrive = -10;
  waitUntil(autoAbort || LineTrackerLeft.reflectivity() > 40 || LineTrackerRight.reflectivity() > 40);
  
  autoDrive = 0;
  Drivetrain.setStopping(coast);
  waitUntil(autoAbort || !intakeMoving);
}

int trayUpDrive ()
{
  waitUntil(autoAbort || tray.position(deg) > 300);
  forwardFunction(1.5, 3, 5, 3, false);
  return 0;
}

void trayUp() {
  if(!trayMoving) {
    trayMoving = true;
    autoIntake = 0;
    autoArms = -10;
    task trayUpDriveTask ( trayUpDrive );

    double tempTray;
    while (tray.position(deg) < 700 && !autoAbort) {
      tempTray = ( tray.position(deg) * -0.139 + 110 );
      if (tray.position(deg) > 650) {
        tempTray = 19.65;
      } else if (tray.position(deg) > 400) {
        autoIntake = 0;
      } else if (tray.position(deg) > 0) {
        autoIntake = -5;
      } else {
        autoIntake = 0;
      }
      autoTray = tempTray;
      vex::task::sleep(20);
    }
    autoTray = 0;
    autoIntake = 0;
    autoArms = 0;
    autoDrive = 0;
    trayMoving = false;
  }
}

int trayDownDrive()
{
    autoDrive = -25;
    wait(0.1, sec);
    intakeSpin(360, -50);
    autoDrive = 0;
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
    task task6 = task( trayDownDrive );
    while (tray.position(deg) > 0 && !autoAbort){
      autoTray = ( ( tray.position(deg) * -0.32 -50));
      vex::task::sleep(20);
    }
    autoTray = 0;
    trayMoving = false;
  }
}

void trayStart ()
{
  autoAbortTray = false;
  if (tray.position(deg) > 10){
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
  waitUntil(autoAbort || fabs(arms.position(deg)) >= fabs(degrees * 5));
  autoArms = 0;
  arms.setBrake(brakeType);
}

void armsDown ()
{
    if(!armsMoving) {
    armsMoving = true;
    while (arms.position(deg) > 0 && !autoAbort)
    {
      autoArms = ( ( arms.position(deg) * -0.07 + 100 ) * -1);
      vex::task::sleep(20);
    }
    autoArms = 0;
    armsMoving = false;
  arms.stop(brake);
  armsPos = down;
  }
}

void armsHigh ()
{
  if(!armsMoving) {
    if(armsPos == down) {
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(180, -100);
      while (arms.position(deg) < 800 && !autoAbort) 
      {
        autoArms = ( arms.position(deg) * -0.1 + 150 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
      arms.stop(hold);
      armsPos = high;
    } else {
      // intakeSpin(20, -100);
      autoArms = -75;
      intakeSpin(180, -100);
      waitUntil(autoAbort || arms.position(deg) < 750);
      autoArms = 0;
      armsDown();
    }
  }
}

void armsLow ()
{
  if(!armsMoving) { // are the arms moving?
    if(armsPos == down) {
      armsMoving = true;
      autoIntake = 0;
      intakeSpin(180, -100);
      while (arms.position(deg) < 600 && !autoAbort) {
        autoArms = ( arms.position(deg) * -0.1 + 150 );
        vex::task::sleep(20);
      }
      autoArms = 0;
      armsMoving = false;
      arms.stop(hold);
      armsPos = low;
    } else {
      intakeSpin(360, -100);
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





void visionDetectFunction (bool turn)
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

  vex::timer intakeTime;
  Flashlight.on();
  
  while (Controller1.ButtonL2.pressing() || Controller1.ButtonL1.pressing()) {

    Controller2.Screen.clearScreen();
    
    Vision.takeSnapshot(cubeOrange);
    objectCount = Vision.objectCount;
    posOrange = (Vision.largestObject.centerX - 165) * 0.5 * orangeToggle;
    heightOrange = Vision.largestObject.height;

    Controller2.Screen.setCursor(1, 1);
    Controller2.Screen.print("Orange H %d", Vision.largestObject.height);
    Controller2.Screen.setCursor(2, 1);
    Controller2.Screen.print("Orange X %d", Vision.largestObject.centerX - 165);

    Vision.takeSnapshot(cubePurple);
    objectCount = objectCount + Vision.objectCount;
    posPurple = (Vision.largestObject.centerX - 165) * 0.5 * purpleToggle;
    heightPurple = Vision.largestObject.height;

    Vision.takeSnapshot(cubeGreen);
    objectCount = objectCount + Vision.objectCount;
    posGreen = (Vision.largestObject.centerX - 165);
    heightGreen = Vision.largestObject.height;



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
  tray.resetPosition();
}

void test()
{
  armsMove(25, 50);
  wait(0.5, sec);
  armsDown();
}


















/*===========================================================================*/

void pre_auton( void ) {
  Flashlight.off();
  Inertial.calibrate();
  menuLcdDraw();
  controllerDraw();
  tray.setStopping(brake);
  tray.setTimeout(1, seconds);

  Controller1.ButtonY.pressed(trayUp);
  Controller1.ButtonX.pressed(trayStart);
  Controller1.ButtonX.released(trayStop);

  Controller1.ButtonR2.pressed(intakeIn);
  Controller1.ButtonR1.pressed(intakeOutSlow);

  Controller1.ButtonL2.pressed(visionTurnFunction);
  Controller1.ButtonL1.pressed(visionStrafeFunction);

  Controller1.ButtonUp.pressed(armsHigh);
  Controller1.ButtonDown.pressed(armsLow);
  Controller1.ButtonLeft.pressed(intakeInSlow);
  Controller1.ButtonDown.pressed(intakeOut);




  Controller2.ButtonLeft.pressed(orangeToggleButton);
  Controller2.ButtonUp.pressed(purpleToggleButton);
  Controller2.ButtonRight.pressed(greenToggleButton);

  Controller2.ButtonY.pressed(goalDrive);
  Controller2.ButtonX.pressed(trayUp);
  Controller2.ButtonA.pressed(trayDown);

  Controller2.ButtonR1.pressed(trayReset);



  // Drivetrain.setTimeout(3, seconds);
  arms.setTimeout(1, seconds);
  arms.setStopping(brake);

  intake.setTimeout(1, seconds);
  intake.setStopping(hold);



  Inertial.calibrate();

  task task1 = task( motorTask );
  autonTaskStart();


  while (!Competition.isAutonomous() || !Competition.isEnabled()) {
    menuLcdTouch();
    vex::task::sleep(20);
  }
}

/*===========================================================================*/

void autonomous( void ) {
  autonIndicator();
  autonInitialize();
  autonRun(currentPage);

  wait(0.5, sec);

  return;
}

/*===========================================================================*/

void usercontrol( void ) {
  while (1) {
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

    // if(leftIntakeSwitch.pressing() && rightIntakeSwitch.pressing() ){
    //   intakeJammed = 1;
    // } else {
    //   intakeJammed = -1;
    // }


    stickForward = Controller1.Axis2.position();
    stickStrafe = Controller1.Axis1.position() * strafeSpeedP;
    stickTurn = Controller1.Axis4.position() * (Controller1.Axis3.position() + 150) / 200;





    if(Controller2.Axis2.position() < - 5 || Controller2.Axis2.position() > 5)
    {
      if(Controller2.ButtonR2.pressing()) 
      {
        trayStick = 0;
        armsStick = Controller2.Axis2.position();
      } else {
        armsStick = 0;
        trayStick = Controller2.Axis2.position();
      }
    } else {
      trayStick = 0;
      armsStick = 0;
    }



    if (intakeLeft.torque() > 1.05 || intakeRight.torque() > 1.05)
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

    // Vision.setLedBrightness(100);
    // Vision.setLedColor(244, 244, 244);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(LineTrackerRight.reflectivity());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(LineTrackerLeft.reflectivity());
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(LineTrackerTray.reflectivity());


    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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