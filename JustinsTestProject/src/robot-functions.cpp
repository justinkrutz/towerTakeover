#include "vex.h"

#include "controller-buttons.h"
#include "robot-functions.h"

namespace RobotFunctions {

// Test function that counts up to 49 in the terminal.
void countUpTask() {
  printf("start\n");
  int count = 0;

  repeat(50) {
    printf("Up %d\n", count++);
    task::sleep(20);
  }
}

// Test function that counts down to -49 in the terminal.
void countDownTask() {
  printf("start\n");
  int count = 0;

  repeat(50) {
    printf("Down %d\n", count--);
    task::sleep(20);
  }
}

// Test function that prints to the terminal.
void singleUseButton() {
  printf("singleUseButton\n");
}

// Dectect and cycle through warnings on the controller screen.
void checkForWarnings() {
  while (1) {
    WARN_BOOL(TestMotor1, installed());
    WARN_BOOL(TestMotor2, installed());
    WARN_BOOL(Vision, installed());
    WARN_BOOL(Inertial, installed());
    WARN_BOOL(Controller2, installed());
    WARN_BOOL(Brain.SDcard, isInserted());
    WARN_RANGE(Inertial, rotation(), -2, 2);

    task::sleep(10);
  }
}

/*===========================================================================*/

// Abort the test 
void abortest0() {
  if (ControllerButtons::Group::test.gSubGroup == 0) {
    ControllerButtons::Group::test.gThread.interrupt();
  }
}

void abortest1() {
  if (ControllerButtons::Group::test.gSubGroup == 1) {
    ControllerButtons::Group::test.gThread.interrupt();
  }
}

void setCallbacks() {
  using namespace ControllerButtons;
  buttonCallbacks = {
      {Controller1.ButtonA,     false, &Group::test,  0, countDownTask},
      {Controller1.ButtonY,     false, &Group::test,  0, countUpTask},
      {Controller1.ButtonX,     false, &Group::test,  0, singleUseButton},
      {Controller1.ButtonRight, false, &Group::test,  1, countDownTask},
      {Controller1.ButtonLeft,  false, &Group::test,  1, countUpTask},
      {Controller1.ButtonLeft,   true, &Group::abort, 0, abortest1},
      {Controller1.ButtonUp,    false, &Group::test,  1, singleUseButton},
      {Controller1.ButtonB,     false, &Group::abort, 0, abortest0},
      {Controller1.ButtonDown,  false, &Group::abort, 0, abortest1},
  };
}

} // namespace RobotFunctions