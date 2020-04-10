#include "vex.h"

#include <bits/stdc++.h>


#include "driverControl.h"
#include "controllerMenu.h"
#include "robotFunctions.h"

using namespace vex;


thread menuThread;
thread driveThread;
thread otherThread;

    struct buttonStruct {
      controller::button button;
      thread * Thread;
      void (* function)();

      bool wasTriggered;
    };
    static std::vector<buttonStruct> buttonCallbacks;

void runButtons() {
  // Cycle through all button callbacks.
  for (auto &buttonCallback : buttonCallbacks) {
    bool isPressing = buttonCallback.button.pressing();
    bool wasPressed = (isPressing && !buttonCallback.wasTriggered);
    bool wasReleased = (!isPressing && buttonCallback.wasTriggered);

    // If the button has been pressed and the thread isn't running
    if (wasPressed && !buttonCallback.Thread->joinable()) {

      // set the function to not run when the button is held
      buttonCallback.wasTriggered = true;

      //Run the function in a separate thread
      *buttonCallback.Thread = thread(buttonCallback.function);

    } else if (wasReleased) {
      buttonCallback.wasTriggered = false;
    }
  }
}

void abortEverything()
{
  driveThread.interrupt();
  menuThread.interrupt();
  otherThread.interrupt();
}

void setCallbacksDriverMode() {
  buttonCallbacks = {
    {Controller1.ButtonA,     &driveThread, countDownTask},
    {Controller1.ButtonY,     &driveThread, countUpTask},
    {Controller1.ButtonX,     &driveThread, singleUseButton},
    {Controller1.ButtonRight, &otherThread, countDownTask},
    {Controller1.ButtonLeft,  &otherThread, countUpTask},
    {Controller1.ButtonUp,    &otherThread, singleUseButton}
  };
}

void setCallbacksAutonSelect() {
  buttonCallbacks = {
    {Controller1.ButtonRight, &menuThread, voidLambda( ControllerMenu.scrollRight() )},
    {Controller1.ButtonLeft,  &menuThread, voidLambda( ControllerMenu.scrollLeft() )},
    {Controller1.ButtonA,     &menuThread, voidLambda( ControllerMenu.select() )},
    {Controller1.ButtonB,     &menuThread, voidLambda( ControllerMenu.back() )},
  };
  // buttonCallbacks[0].function = voidLambda( ControllerMenu.scrollRight() );
  // menuThread = this->scrollRight
}

// driverControl DriverControl;