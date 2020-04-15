#include "vex.h"


#define WARN(device ,member) \
if (!device.member()){ \
  const char * deviceChar = "" #device; \
  const char * message = "Not " #member; \
  Controller1.Screen.clearScreen(); \
  Controller1.Screen.setCursor(1, 0); \
  Controller1.Screen.print(deviceChar); \
  Controller1.Screen.setCursor(2, 0); \
  Controller1.Screen.print(message); \
  wait (1, sec); \
}

namespace RobotFunctions {
  extern void countUpTask();
  extern void countDownTask();
  extern void singleUseButton();

  extern void checkForWarnings();
  
  extern void setCallbacks();
}