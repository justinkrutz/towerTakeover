#include "vex.h"

using namespace vex;

int deployTray()
{
  tray.setBrake(brake);
  autoTray = 100;
  waitUntil(tray.position(deg) > 200);
  autoTray = -70;
  wait(0.5, sec);
  autoTray = -20;
  wait(1, sec);
  autoTray = 0;
  tray.setBrake(coast);
  wait(1, sec);
  tray.resetPosition();
  tray.setBrake(hold);
  return 0;
}

void auton5()
{
  forwardFunction(20, 5, 50, 5);
  forwardFunction(-20, 5, 50, 5);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("5");
 
}

void auton11()
{
  forwardFunction(2, 5, 50, 5);

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("11");
 
}

void blueSmallGoal()
{
  Brain.Timer.reset();
  Drivetrain.setStopping(hold);
  task deployTrayTask = ( deployTray );

  forwardFunction(8, 20, 50, 5, false);

  waitUntil(!tipWheel);
  wait(500, msec);
  autoIntake = -100;
  wait(200, msec);
  autoIntake = 100;
  waitUntil(!forwardStruct.isMoving);

  forwardFunction(14, 5, 35, 25, true);
  forwardFunction(7, 25, 25, 5, false);
  autoIntake = 50;
  armsMove(27, 100);
  autoIntake = 100;
  wait(0.3, sec);
  armsDown();
  wait(0.2, sec);
  // forwardFunction(-24, 20, 100, 5, false);
  // strafeFunction(-15, 20, 50, 50, true);
  // strafeFunction(-11, 20, 100, 5, true);
  // forwardFunction(27, 20, 35, 5, true);
  // autoIntake = 0;
  // turnFunction(-90, 20, 60, 5, false);
  // forwardFunction(-8, 20, 100, 5, false);
  // strafeFunction(-10, 5, 50, 50, true);
  // autoIntake = 100;
  // strafeFunction(-17, 50, 100, 5, true);
  // autoIntake = 0;
  // gyroActive = false;
  // strafeOutput = -10;
  // forwardFunction(5, 20, 75, 30, true);
  // goalDrive();
  // gyroYawStart = Inertial.rotation(deg) + headingDeg;
  // strafeOutput = -5;
  // trayUp();
  // strafeOutput = -0;
  // trayDown();

  Drivetrain.setStopping(coast);
  



  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print(Brain.Timer.time(msec));
}

void autonRun(int auton)
{
  switch(auton)
  {
    case 0:
    blueSmallGoal();
    break;
    case 5:
    auton5();
    break;
    case 11:
    auton11();
    break;
    case 16:
    blueSmallGoal();
    break;
  }
}