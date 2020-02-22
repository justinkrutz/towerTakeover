#include "vex.h"

using namespace vex;

int deployTray()
{
  tray.setBrake(coast);
  tray.setPosition(-100, deg);
  while (!autoAbort && tray.position(deg) < 250){
  autoTray = tray.position(deg) * -1 + 255;
  task::sleep(5);
  }

  while (!autoAbort && tray.position(deg) > 100){
    if (tray.position(deg) < 250) autoTray = ((tray.position(deg) - 255));
    else autoTray = -5;
  task::sleep(5);
  }

  while (!autoAbort && tray.position(deg) > 1){
  autoTray = tray.position(deg) * -1 - 5;
  task::sleep(5);
  }

  autoTray = 0;
  task::sleep(1000);
  tray.setBrake(hold);
  return 0;
}

int autonStop()
{
  waitUntil(Brain.Timer.time(msec) >= 15000);
  autoAbort = true;
  return 0;
}



void none()
{
  task deployTrayTask = ( deployTray );
  forwardFunction(11, 20, 50, 10, false);
  waitUntil(!tipWheel);
  task::sleep(450);
  autoIntake = -100;
  task::sleep(200);
  autoIntake = 100;
  task::sleep(1000);
  autoIntake = 0;
}



void smallGoal (int alliance)
{
  allianceColor = alliance;

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
  task::sleep(450);
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
  autoIntake = 80;
  armsMove(30 ,100);
  autoIntake = 100;
  task::sleep(300);
        printf("%f Time after arms up\n", Brain.Timer.time(msec));
        printf("%f InchesF after arms up\n", forwardDistance);
  armsMove(2,-35);
  armsDown();
        printf("%f Time after arms down\n", Brain.Timer.time(msec));
        printf("%f InchesF after arms down\n", forwardDistance);
  forwardFunction(-24, 20, 100, 5, false);
  strafeFunction(-15, 20, 50, 50, true);
  strafeFunction(-11, 20, 100, 5, true);
  forwardFunction(27, 20, 30, 5, true);
  autoIntake = 0;
  turnFunction(-90, 20, 60, 5, false);
  forwardFunction(-8, 20, 100, 5, false);
  strafeFunction(-10, 5, 50, 50, true);
  autoIntake = 100;
  strafeFunction(-19, 50, 100, 5, true);
  gyroActive = false;
  strafeOutput = -20 * allianceColor;
  goalDrive();
        printf("%f Time after goalDrive\n", Brain.Timer.time(msec));
        printf("%f InchesF after goalDrive\n", forwardDistance);
  Drivetrain.setStopping(hold);
  strafeOutput = -5 * allianceColor;
  gyroYawStart = Inertial.rotation(deg) + headingDeg;
  trayUp();
        printf("%f Time after trayUp\n", Brain.Timer.time(msec));
        printf("%f InchesF after trayUp\n", forwardDistance);
  strafeOutput = 0 * allianceColor;
  trayDown();
        printf("%f Time end\n", Brain.Timer.time(msec));
        printf("%f InchesF end\n", forwardDistance);

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print(Brain.Timer.time(msec));
}

void blueSmallGoal()
{
  smallGoal(blueAlliance);
}

void redSmallGoal()
{
  smallGoal(redAlliance);
}

void skillsOne()
{
        printf("%f Time start skills\n", Brain.Timer.time(msec));
        printf("%f InchesF start skills\n", forwardDistance);
  Drivetrain.setStopping(hold);
  blueSmallGoal();
  
  strafeOutput = -10;
  task::sleep(500);
  gyroYawStart = Inertial.rotation(deg) - headingDeg;
  gyroActive = true;
  strafeOutput = 0;
        printf("%f Time gyro reset\n", Brain.Timer.time(msec));
        printf("%f InchesF gyro reset\n", forwardDistance);

  strafeFunction(10, 5, 50, 5, true);
  turnFunction(87.417183, 15, 50, 5, true);
  strafeFunction(8.25, 5, 50, 5, true);
  autoIntake = 100;
  forwardFunction(35, 5, 100, 5, true);
  task::sleep(500);
  armsLow();
  forwardFunction(5, 5, 50, 5, true);
  intakeSpin(340, -100);
  forwardFunction(-5, 5, 50, 5, true);
  armsDown();
  strafeFunction(-6.5, 5, 50, 5, true);
  autoIntake = 100;
  forwardFunction(7, 5, 25, 5, true);
  forwardFunction(-21.5, 5, 50, 5, true);
  autoIntake = 0;
  turnFunction(-87.417183, 15, 50, 5, true);
  armsLow();
  forwardFunction(11, 5, 50, 5, true);
  intakeSpin(340, -100);

  forwardFunction(-30, 5, 50, 5, true);
  armsDown();
  turnFunction(-174.834366, 15, 50, 5, true);
  strafeFunction(11, 5, 50, 5, true);
  autoIntake = 100;
  forwardFunction(8.5, 5, 50, 5, true);
  forwardFunction(-5, 5, 50, 5, true);
  armsHigh();
  forwardFunction(8.5, 5, 50, 5, true);
  forwardOutput = 20;
  task::sleep(500);
  forwardOutput = 0;
  armsHigh();

  

  

  Drivetrain.setStopping(coast);
        printf("%f Time end\n", Brain.Timer.time(msec));
        printf("%f InchesF end\n", forwardDistance);
}

void autonRun(int auton)
{
  switch(auton)
  {
    case 0:
    none();
    break;
    case 8:
    skillsOne();
    break;
    case 5:
    redSmallGoal();
    break;
    case 10:
    none();
    break;
    case 16:
    blueSmallGoal();
    break;
    default:;
  }
}