#include "vex.h"

#include <bits/stdc++.h>

#define voidLambda( function ) [](void) {function;}


extern void runButtons();
extern void abortEverything();
extern void setCallbacksDriverMode();
extern void setCallbacksAutonSelect();


// class driverControl {
//   public:
//     void runButtons( void );
//     void abortEverything( void );
//     class setCallbacks {
//       public:
//         void driverMode( void );
//         void autonSelect( void );
//     };
//   private:
//     struct buttonStruct {
//       controller::button button;
//       thread * Thread;
//       void (* function)();

//       bool wasTriggered;
//     };
//     static std::vector<buttonStruct> buttonCallbacks;
// };

// extern driverControl DriverControl;