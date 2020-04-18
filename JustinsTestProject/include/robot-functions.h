#include "vex.h"

#include <bits/stdc++.h>

#define WARN(device, messageToPrint, warnIf)                                   \
  if (warnIf) {                                                                \
    const char *deviceChar = "" #device;                                       \
    Controller1.Screen.clearScreen();                                          \
    Controller1.Screen.setCursor(1, 0);                                        \
    Controller1.Screen.print(deviceChar);                                      \
    Controller1.Screen.setCursor(2, 0);                                        \
    Controller1.Screen.print(messageToPrint);                                  \
    wait(1, sec);                                                              \
  }

#define WARN_BOOL(device, member)                                              \
  {                                                                            \
    const char *message = "Not " #member;                                      \
    WARN(device, message, !device.member)                                      \
  }

#define WARN_RANGE(device, member, lowerRange, upperRange)                     \
  WARN(device, "Out of Range",                                                 \
       !(device.member > lowerRange && device.member < upperRange))

namespace RobotFunctions {
void countUpTask();
void countDownTask();
void singleUseButton();

void checkForWarnings();

void setCallbacks();
} // namespace RobotFunctions