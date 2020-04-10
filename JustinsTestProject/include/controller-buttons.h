#include "vex.h"

#include <bits/stdc++.h>


#define VOID_LAMBDA( function ) [](void) {function;}


namespace ControllerButtons {
  namespace Thread {
    extern thread menu;
    extern thread drive;
    extern thread other;
    extern thread abort;
  }

  extern void runButtons();

  struct buttonStruct {
  controller::button button;
  bool triggerOnRelease;
  thread * Thread;
  void (* function)();

  bool wasTriggered;
  };
  extern std::vector<buttonStruct> buttonCallbacks;
}