#include "vex.h"

using namespace vex;

int testTimeLimit ()
{
  wait(15, sec);
  autoAbort = true;
  return 0;
}

void deployTray()
{
  tray.setPosition(-66, deg);
  forwardFunction(6, 5, 20, 5);
  tray.rotateTo(180, deg, 100, rpm);
  tray.spinFor(3, sec, -20, rpm);
  tray.resetPosition();
  // forwardFunction(6, -24, 5, 50, 5);
  // forwardFunction(-12, 1, 100, 100, 100);

  // intake.spin(reverse, 200, rpm);
  // wait(1, sec);
  // intake.spin(fwd, 200, rpm);
  // wait(1, sec);
  // intake.stop();
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
  task task7 = task( testTimeLimit );
  autoIntake = 100;
  forwardFunction(14, 20, 100, 25, true);
  forwardFunction(8, 25, 35, 25, true);
  forwardFunction(7, 25, 25, 5, false);
  armsMove(35, 100);
  wait(0.3, sec);
  armsDown();
  wait(0.2, sec);
  forwardFunction(-24, 20, 100, 5, false);
  strafeFunction(-15, 20, 50, 50, true);
  strafeFunction(-11, 20, 100, 5, true);
  forwardFunction(27, 20, 35, 5, true);
  turnFunction(-90, 20, 100, 5, false);
  forwardFunction(-8, 20, 40, 5, true);
  strafeFunction(-34, 20, 100, 5, true);
  autoIntake = 0;
  forwardFunction(5, 20, 75, 30, true);
  strafeOutput = -10;
  goalDrive();
  // strafeFunction(-5, 10, 10, 10, false);
  strafeOutput = -5;
  trayUp();
  strafeOutput = -0;
  trayDown();

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