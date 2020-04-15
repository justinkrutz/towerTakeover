#include "vex.h"

#include <bits/stdc++.h>


#define VOID_LAMBDA( function ) [](void) {function;}


namespace ControllerButtons {
  class GroupClass {
    public:
      thread gThread;
      int gSubGroup;
  };
  namespace Group {
    extern GroupClass menu;
    extern GroupClass drive;
    extern GroupClass other;
    extern GroupClass abort;
  }

  extern void runButtons();

  struct buttonStruct {
    controller::button button;
    bool triggerOnRelease;
    GroupClass * group;
    int subGroup;
    void (* function)();

    bool wasTriggered;
  };
  extern std::vector<buttonStruct> buttonCallbacks;
}