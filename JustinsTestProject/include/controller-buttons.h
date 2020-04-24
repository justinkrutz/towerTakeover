#include "vex.h"

#include <bits/stdc++.h>

namespace controllerbuttons {
extern thread no_thread;

struct MacroGroup {
  bool is_running;
  thread *last_run_thread = &no_thread;
};

struct ButtonStruct {
  // Button to be checked
  controller::button *button;
  // Should the functon be started when the button us pressed or released
  bool trigger_on_release;
  std::vector<MacroGroup *> macro_groups;
  void (*function)();

  bool was_triggered;
  thread button_thread;
};


/**
 * Checks through each struct in the vector one by one,
 * and runs starts the function running on a seperate thread if:
 *   1. The associated button is being pressed,
 *   2. There is not currently a function running in the same group,
 *   3. Last time around the loop, either the button wasn't pressed,
 *      or the group was running.
 * If the function is set to trigger_on_release, then it will run
 * when the button is released, instead of pressed.
 *
 * Subgroups are only for external reference, and do not effect what the buttons do.
 *
 * Should be run in a loop.
 */
void runButtons();
void interruptMacroGroup(std::vector<MacroGroup *> macro_groups);

extern std::vector<MacroGroup *> macro_group_vector;

// Stores what buttons should run which functions
// Is writen to in ::setCallback functions
extern std::vector<ButtonStruct> button_callbacks;

} // namespace controllerbuttons


// #define CREATE_MACRO_GROUP(name) \
// MacroGroup name; \
// name.last_run_thread = &controllerbuttons::no_thread; \
// controllerbuttons::macro_group_vector.push_back(name);