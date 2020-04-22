#include "vex.h"

#include "controller-buttons.h"
#include "robot-functions.h"

namespace robotfunctions {

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

void countUpTaskHold() {
  countUpTask();
}

// Abort the test 
void abortTest() {
    controllerbuttons::threads::test.interrupt();
}

void abortTestHold() {
  // if (controllerbuttons::group::test.lastTriggeredBy == &Controller1.ButtonLeft) {
    // controllerbuttons::group::test.gThread.interrupt();
    thread(countUpTaskHold).interrupt();
  // }
}

void setCallbacks() {
  using namespace controllerbuttons;
  buttonCallbacks = {
      {&Controller1.ButtonA,     false, {&threads::test},  &countDownTask},
      {&Controller1.ButtonY,     false, {&threads::test},  &countUpTask},
      {&Controller1.ButtonX,     false, {&threads::test},  &singleUseButton},
      {&Controller1.ButtonRight, false, {&threads::test},  &countDownTask},
      {&Controller1.ButtonLeft,  false, {&threads::test},  &countUpTaskHold},
      {&Controller1.ButtonLeft,   true, {&threads::abort}, &abortTestHold},
      {&Controller1.ButtonUp,    false, {&threads::test},  &singleUseButton},
      {&Controller1.ButtonB,     false, {&threads::abort}, &abortTest},
      {&Controller1.ButtonDown,  false, {&threads::abort}, &abortTest},
  };
}

} // namespace robotfunctions