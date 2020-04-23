#include "vex.h"

#include <bits/stdc++.h>

#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace controllerbuttons {
thread no_thread;

std::vector<MacroGroup *> macro_group_vector;
// Stores what buttons should run which functions
// Is writen to in ::setCalback functions
std::vector<ButtonStruct> button_callbacks;
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
  for (auto &macro_group : macro_group_vector) {
    macro_group->is_running = macro_group->last_run_thread->joinable();
  }

  // Cycle through all button callbacks
  for (auto &button_callback : button_callbacks) {
    bool was_pressed  = ( button_callback.button->pressing() &&
                        !button_callback.was_triggered);
    bool was_released = (!button_callback.button->pressing() &&
                         button_callback.was_triggered);
    bool is_running;
    for (auto &macro_group : button_callback.macro_groups) {
      is_running = macro_group->is_running;
    }

    // printf("ptr %p\n", macro_group_vector[0]);
    // printf("ptr %p\n", button_callback.macro_groups[0]);
    // If the button has been pressed and the thread isn't running
    if (was_pressed && !is_running) {
      // Set the function to not run when the button is held
      button_callback.was_triggered = true;
      if (button_callback.trigger_on_release) continue;
    } else if (was_released) {
      button_callback.was_triggered = false;
      if (!button_callback.trigger_on_release) continue;
    } else {
      continue;
    }

    // Run the function in a separate thread
    button_callback.button_thread = thread(button_callback.function);
    for (auto &macro_group : button_callback.macro_groups) {
      macro_group->is_running = true;
      macro_group->last_run_thread = &button_callback.button_thread;
    }
  }
}

void interruptMacroGroup(std::vector<MacroGroup *> macro_groups) {
  for (auto &macro_group : macro_groups) {
    macro_group->last_run_thread->interrupt();
  }
}
} // namespace controllerbuttons