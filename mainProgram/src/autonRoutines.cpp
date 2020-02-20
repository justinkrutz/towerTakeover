#include "vex.h"

using namespace vex;

int deployTray()
{
  tray.setBrake(brake);
  autoTray = 100;
  waitUntil(tray.position(deg) > 200);
  autoTray = -70;
  task::sleep(500);
  autoTray = -20;
  task::sleep(100);
  autoTray = 0;
  tray.setBrake(coast);
  task::sleep(1000);
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
        printf("\n%f Time start\n", Brain.Timer.time(msec));
        printf("%f InchesF start\n", forwardDistance);
  forwardFunction(11, 20, 50, 10, false);
        printf("%f Time after FF1\n", Brain.Timer.time(msec));

  waitUntil(!tipWheel);
        printf("%f Time after wait1\n", Brain.Timer.time(msec));
        printf("%f InchesF after wait1\n", forwardDistance);
  task::sleep(500);
  autoIntake = -100;
  task::sleep(200);
  autoIntake = 100;
  waitUntil(LineTrackerTray.reflectivity() > 5 || Brain.Timer.time(msec) > 1600);
        printf("%f Time after deploy\n", Brain.Timer.time(msec));
        printf("%f InchesF after deploy\n", forwardDistance);
  waitUntil(!forwardStruct.isMoving);
        printf("%f Time after wait2\n", Brain.Timer.time(msec));
        printf("%f InchesF after wait2\n", forwardDistance);

  forwardFunction(11, 10, 35, 25, true);
        printf("%f Time after FF2\n", Brain.Timer.time(msec));
        printf("%f InchesF after FF2\n", forwardDistance);
  forwardFunction(8, 25, 25, 5, false);
        printf("%f Time after FF3\n", Brain.Timer.time(msec));
        printf("%f InchesF after FF3\n", forwardDistance);
  autoIntake = 60;
  armsMove(27,100);
  autoIntake = 100;
  task::sleep(300);
        printf("%f Time after arms up\n", Brain.Timer.time(msec));
        printf("%f InchesF after arms up\n", forwardDistance);
  armsMove(2,-35);
  armsDown();
        printf("%f Time after arms down\n", Brain.Timer.time(msec));
        printf("%f InchesF after arms down\n", forwardDistance);
  forwardFunction(-24, 20, 100, 5, false);
  task::sleep(50);
  autoIntake = 0;
  // strafeFunction(-15, 20, 50, 50, true);
  // strafeFunction(-11, 20, 100, 5, true);
  // forwardFunction(27, 20, 35, 5, true);
  // autoIntake = 0;
  // turnFunction(-90, 20, 60, 5, false);
  // forwardFunction(-8, 20, 100, 5, false);
  // strafeFunction(-10, 5, 50, 50, true);
  // autoIntake = 100;
  // strafeFunction(-17, 50, 100, 5, true);
  autoIntake = 0;
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
  


        printf("%f Time end\n", Brain.Timer.time(msec));
        printf("%f InchesF end\n", forwardDistance);

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