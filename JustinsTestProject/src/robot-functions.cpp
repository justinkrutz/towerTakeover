#include "vex.h"

#include "controller-buttons.h"

namespace RobotFunctions {

  /*===========================================================================*/

  void countUpTask() {
    printf("start\n");
    int count = 0;

    repeat(50) {
      printf("Up %d\n", count++);
      
      // don't hog the cpu :)
      task::sleep( 20 );
    }
  }

  void countDownTask() {
    printf("start\n");
    int count = 0;

    repeat(50) {
      printf("Down %d\n", count--);
      
      // don't hog the cpu :)
      task::sleep( 20 );
    }
  }

  void singleUseButton() {
    printf("singleUseButton\n");
  }

 /*===========================================================================*/

  void abortDrive() {
    ControllerButtons::Thread::drive.interrupt();
  }

  void abortOther() {
    ControllerButtons::Thread::other.interrupt();
  }

  void setCallbacks() {
    ControllerButtons::buttonCallbacks = {
      {Controller1.ButtonA,     false, &ControllerButtons::Thread::drive, countDownTask},
      {Controller1.ButtonY,     false, &ControllerButtons::Thread::drive, countUpTask},
      {Controller1.ButtonX,     false, &ControllerButtons::Thread::drive, singleUseButton},
      {Controller1.ButtonRight, false, &ControllerButtons::Thread::other, countDownTask},
      {Controller1.ButtonLeft,  false, &ControllerButtons::Thread::other, countUpTask},
      // {Controller1.ButtonLeft,   true, &ControllerButtons::Thread::abort, abortOther},
      {Controller1.ButtonUp,    false, &ControllerButtons::Thread::other, singleUseButton},
      {Controller1.ButtonB,     false, &ControllerButtons::Thread::abort, abortDrive},
      {Controller1.ButtonDown,  false, &ControllerButtons::Thread::abort, abortOther},
    };
  }

}