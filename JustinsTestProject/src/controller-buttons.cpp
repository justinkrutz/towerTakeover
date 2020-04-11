#include "vex.h"

#include <bits/stdc++.h>


#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace ControllerButtons {
  namespace Thread {
  thread menu;
  thread drive;
  thread other;
  thread abort;
  }

  std::vector<buttonStruct> buttonCallbacks;

  void getAroundVexThreadBug(void * func) {
  ((void(*)()) func)();
  }

  void runButtons() {
    // Cycle through all button callbacks.
    for (auto &buttonCallback : buttonCallbacks) {
      bool isPressing = buttonCallback.button.pressing();
      bool wasPressed = (isPressing && !buttonCallback.wasTriggered);
      bool wasReleased = (!isPressing && buttonCallback.wasTriggered);
      // If the button has been pressed and the thread isn't running
      if (wasPressed && (!buttonCallback.Thread->joinable() || buttonCallback.triggerOnRelease)) {

        // set the function to not run when the button is held
        buttonCallback.wasTriggered = true;

        //Run the function in a separate thread
        if (!buttonCallback.triggerOnRelease) {
          *buttonCallback.Thread = thread(getAroundVexThreadBug, (void *)buttonCallback.function);
          printf("thread id %ld\n", buttonCallback.Thread->get_id());
        }

      } else if (wasReleased) {
        buttonCallback.wasTriggered = false;
        if (buttonCallback.triggerOnRelease) {
          *buttonCallback.Thread = thread(getAroundVexThreadBug, (void *)buttonCallback.function);
        }
      }
    }
  }
}