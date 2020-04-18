#ifndef controller_buttons_h_
#define controller_buttons_h_

#include "vex.h"

#include <bits/stdc++.h>

namespace ControllerButtons {
struct GroupClass {
  thread gThread;
  int gSubGroup;
};
namespace Group {
extern GroupClass menu;
extern GroupClass test; 
extern GroupClass abort;
} // namespace Group

void runButtons();

struct buttonStruct {
  controller::button button;
  bool triggerOnRelease;
  GroupClass *group;
  int subGroup;
  void (*function)();

  bool wasTriggered;
};
extern std::vector<buttonStruct> buttonCallbacks;
} // namespace ControllerButtons

#endif // controller_buttons_h_