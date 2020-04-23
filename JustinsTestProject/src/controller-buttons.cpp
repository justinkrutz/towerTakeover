#include "vex.h"

#include <bits/stdc++.h>

#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace controllerbuttons {
thread noThread;

std::vector<MacroGroup *> MacroGroupVector;
// Stores what buttons should run which functions
// Is writen to in ::setCalback functions
std::vector<ButtonStruct> buttonCallbacks;

/**
 * Checks through each struct in the vector one by one,
 * and starts the function on a seperate thread, but only if:
 *   1. The associated button is being pressed,
 *   2. There is not currently a function running in the same group,
 *   3. Last time around the loop, either the button wasn't pressed,
 *      or the group was running.
 * If the function is set to triggerOnRelease, then it will run
 * when the button is released, instead of pressed.
 *
 * Subgroups are only for externaly differentiating a running thread, if there are multiple callbacks to
 * the same function and thread, and do not affect what the buttons do. 
 * 
 * Should be run in a loop.
 */
void runButtons() {
  for (auto &macroGroup : MacroGroupVector) {
    macroGroup->isRunning = macroGroup->lastRunThread->joinable();
  }

  // Cycle through all button callbacks
  for (auto &buttonCallback : buttonCallbacks) {
    bool wasPressed  = ( buttonCallback.button->pressing() &&
                        !buttonCallback.wasTriggered);
    bool wasReleased = (!buttonCallback.button->pressing() &&
                         buttonCallback.wasTriggered);
    bool isRunning;
    for (auto &macroGroup : buttonCallback.macroGroups) {
      isRunning = macroGroup->isRunning;
    }

    // printf("ptr %p\n", MacroGroupVector[0]);
    // printf("ptr %p\n", buttonCallback.macroGroups[0]);
    // If the button has been pressed and the thread isn't running
    if (wasPressed && !isRunning) {
      // Set the function to not run when the button is held
      buttonCallback.wasTriggered = true;
      if (buttonCallback.triggerOnRelease) continue;
    } else if (wasReleased) {
      buttonCallback.wasTriggered = false;
      if (!buttonCallback.triggerOnRelease) continue;
    } else {
      continue;
    }

    // Run the function in a separate thread
    buttonCallback.buttonThread = thread(buttonCallback.function);
    for (auto &macroGroup : buttonCallback.macroGroups) {
      macroGroup->isRunning = true;
      macroGroup->lastRunThread = &buttonCallback.buttonThread;
    }
  }
}

void interruptMacroGroup(std::vector<MacroGroup *> macroGroups) {
  for (auto &macroGroup : macroGroups) {
    macroGroup->lastRunThread->interrupt();
  }
}
} // namespace controllerbuttons