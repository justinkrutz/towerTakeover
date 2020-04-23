#include "vex.h"

#include "controller-buttons.h"
#include "robot-functions.h"


namespace robotfunctions {
controllerbuttons::MacroGroup test1;
controllerbuttons::MacroGroup test2;
controllerbuttons::MacroGroup abort;

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
void abortTest1() {
  controllerbuttons::interruptMacroGroup({&test1});
}

void abortTest2() {
  controllerbuttons::interruptMacroGroup({&test2});
}

void countUpTaskAbort() {
  thread(countUpTaskHold).interrupt();
}
void setCallbacks() {
  using namespace controllerbuttons;
  MacroGroupVector = {&test1, &test2, &abort};
  buttonCallbacks = {
      {&Controller1.ButtonA,     false, {&test1,  &test2},  &countDownTask},
      {&Controller1.ButtonY,     false, {&test1}, &countUpTask},
      {&Controller1.ButtonX,     false, {&test1}, &singleUseButton},
      {&Controller1.ButtonRight, false, {&test2}, &countDownTask},
      {&Controller1.ButtonLeft,  false, {&test2}, &countUpTaskHold},
      {&Controller1.ButtonLeft,   true, {&abort}, &countUpTaskAbort},
      {&Controller1.ButtonUp,    false, {&test2}, &singleUseButton},
      {&Controller1.ButtonB,     false, {&abort}, &abortTest1},
      {&Controller1.ButtonDown,  false, {&abort}, &abortTest2},
  };
}

} // namespace robotfunctions