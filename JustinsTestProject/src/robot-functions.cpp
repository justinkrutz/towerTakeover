#include "vex.h"

#include "robot-functions.h"
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




  void checkForWarnings() {
    while (1) {
      // WARN(TestMotor1, installed);
      // WARN(TestMotor2, installed);
      // WARN(Vision, installed);
      // WARN(Inertial, installed);
      // WARN(Controller2, installed);
      // WARN(Brain.SDcard, isInserted);
      TestMotor1.temperature();

      task::sleep(10);
    } 
  }

 /*===========================================================================*/

  void abortDrive0() {
    if (ControllerButtons::Group::drive.gSubGroup == 0){
      ControllerButtons::Group::drive.gThread.interrupt();
    }
  }

  void abortDrive1() {
    if (ControllerButtons::Group::drive.gSubGroup == 1){
      ControllerButtons::Group::drive.gThread.interrupt();
    }
  }

  void setCallbacks() {
    ControllerButtons::buttonCallbacks = {
      {Controller1.ButtonA,     false, &ControllerButtons::Group::drive, 0, countDownTask   },
      {Controller1.ButtonY,     false, &ControllerButtons::Group::drive, 0, countUpTask     },
      {Controller1.ButtonX,     false, &ControllerButtons::Group::drive, 0, singleUseButton },
      {Controller1.ButtonRight, false, &ControllerButtons::Group::drive, 1, countDownTask   },
      {Controller1.ButtonLeft,  false, &ControllerButtons::Group::drive, 1, countUpTask     },
      {Controller1.ButtonLeft,   true, &ControllerButtons::Group::abort, 0, abortDrive1     },
      {Controller1.ButtonUp,    false, &ControllerButtons::Group::drive, 1, singleUseButton },
      {Controller1.ButtonB,     false, &ControllerButtons::Group::abort, 0, abortDrive0     },
      {Controller1.ButtonDown,  false, &ControllerButtons::Group::abort, 0, abortDrive1     },
    };
  }

}