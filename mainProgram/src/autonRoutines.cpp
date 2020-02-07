#include "vex.h"

using namespace vex;

void auton5()
{
  forwardFunction(0, 20, 5, 50, 5);
  forwardFunction(20, -20, 5, 50, 5);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("5");
 
}

void auton11()
{
  forwardFunction(0, 2, 5, 50, 5);

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("11");
 
}

void autonRun(int auton)
{
  switch(auton)
  {
    case 5:
    auton5();
    break;
    case 11:
    auton11();
    break;
  }
}