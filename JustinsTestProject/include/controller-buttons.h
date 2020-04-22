#include "vex.h"

#include <bits/stdc++.h>

namespace controllerbuttons {

namespace threads {
extern thread menu;
extern thread test;
extern thread abort;
} // namespace group


struct ButtonStruct {

  // Button to be checked
  controller::button *button;

  // Should the functon be started when the button us pressed or released
  bool triggerOnRelease;

  // A 
  std::vector<thread *> buttonThread;
  void (*function)();

  bool wasTriggered;
};

/**
 * Checks through each struct in the vector one by one,
 * and runs starts the function running on a seperate thread if:
 *   1. The associated button is being pressed,
 *   2. There is not currently a function running in the same group,
 *   3. Last time around the loop, either the button wasn't pressed,
 *      or the group was running.
 * If the function is set to triggerOnRelease, then it will run
 * when the button is released, instead of pressed.
 *
 * Subgroups are only for external reference, and do not effect what the buttons do.
 *
 * Should be run in a loop.
 */
void runButtons();

// Stores what buttons should run which functions
// Is writen to in ::setCallback functions
extern std::vector<ButtonStruct> buttonCallbacks;
} // namespace controllerbuttons