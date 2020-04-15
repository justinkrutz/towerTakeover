#include "vex.h"

#include <bits/stdc++.h>


#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace ControllerButtons {
  namespace Group {
    GroupClass menu;
    GroupClass drive;
    GroupClass other;
    GroupClass abort;
  }

  std::vector<buttonStruct> buttonCallbacks;

  void runButtons() {
    // Cycle through all button callbacks.
    for (auto &buttonCallback : buttonCallbacks) {
      bool isPressing = buttonCallback.button.pressing();
      bool wasPressed = (isPressing && !buttonCallback.wasTriggered);
      bool wasReleased = (!isPressing && buttonCallback.wasTriggered);
      // If the button has been pressed and the thread isn't running
      if (wasPressed && (!buttonCallback.group->gThread.joinable())) {

        // set the function to not run when the button is held
        buttonCallback.wasTriggered = true;

        //Run the function in a separate thread
        if (!buttonCallback.triggerOnRelease) {
            buttonCallback.group->gThread = thread(buttonCallback.function);
            buttonCallback.group->gSubGroup = buttonCallback.subGroup;
            printf("thread id %ld\n", buttonCallback.group->gThread.get_id());
        }

      } else if (wasReleased) {
        buttonCallback.wasTriggered = false;
        if (buttonCallback.triggerOnRelease) {
          buttonCallback.group->gThread = thread(buttonCallback.function);
        }
      }
    }
  }
}