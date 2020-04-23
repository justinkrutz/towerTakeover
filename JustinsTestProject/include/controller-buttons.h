#include "vex.h"

#include <bits/stdc++.h>

namespace controllerbuttons {
extern thread noThread;

struct MacroGroup {
  bool isRunning;
  thread *lastRunThread = &noThread;
};

struct ButtonStruct {
  // Button to be checked
  controller::button *button;
  // Should the functon be started when the button us pressed or released
  bool triggerOnRelease;
  std::vector<MacroGroup *> macroGroups;
  void (*function)();

  bool wasTriggered;
  thread buttonThread;
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
void interruptMacroGroup(std::vector<MacroGroup *> macroGroups);

extern std::vector<MacroGroup *> MacroGroupVector;

// Stores what buttons should run which functions
// Is writen to in ::setCallback functions
extern std::vector<ButtonStruct> buttonCallbacks;

} // namespace controllerbuttons


// #define CREATE_MACRO_GROUP(name) \
// MacroGroup name; \
// name.lastRunThread = &controllerbuttons::noThread; \
// controllerbuttons::MacroGroupVector.push_back(name);