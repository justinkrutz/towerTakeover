// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include <bits/stdc++.h>

#include "menuSystem.h"


using namespace vex;


competition Competition;

thread menuThread;
thread driveThread;

#define setVoidFunction( function ) [](void) {function;}
#define setIntFunction( function ) [](thread) {function; return 0;}

  printf("start\n");
  int count = 0;

  }

  // return 0;
}

// void countUpTaskStop() 
// {
//   if (subroutine.function == countUpTask) {
//     subroutine.isRunning = false;
//   }
// }

void countDownTask() {
  printf("start\n");
  int count = 0;

  repeat(50) {
    printf("Down %d\n", count--);
    
    // don't hog the cpu :)
    task::sleep( 20 );
  }

  // return 0;
}


void singleUseButton() 
{
  printf("singleUseButton\n");
  // return 0;
}





struct buttonStruct {
  controller::button button;
  thread * Thread;
  void (* function)();

  bool wasTriggered;
};

std::vector<buttonStruct> buttonCallbacks;

void setDriveButtonCallbacks()
{
  buttonCallbacks = {
    {Controller1.ButtonA,     &driveThread, countDownTask},
    {Controller1.ButtonY,     &driveThread, countUpTask},
    {Controller1.ButtonX,     &driveThread, singleUseButton},
    {Controller1.ButtonRight, &driveThread, countDownTask},
    {Controller1.ButtonLeft,  &driveThread, countUpTask},
    {Controller1.ButtonUp,    &driveThread, singleUseButton}
  };
}



// {
//   subroutine.isRunning = true;
//   function();
//   subroutine.isRunning = false;
//   return 0;
// }

void runButtons()
{
  // Cycle through all button callbacks.
  for (auto &buttonCallback : buttonCallbacks) {
    bool isPressing = buttonCallback.button.pressing();
    bool wasPressed = (isPressing && !buttonCallback.wasTriggered);
    bool wasReleased = (!isPressing && buttonCallback.wasTriggered);

    // If the button has been pressed and the thread isn't running
    if (wasPressed && !buttonCallback.Thread->joinable()) {

      // set the function to not run when the button is held
      buttonCallback.wasTriggered = true;
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
}


// int testTask()
// {
//   runningFunction();
//   return 0;
// }

#define folder 0
#define auton 1
#define sSwitch 2
#define sSlider 3

const char *itemTypeChar(int item) {
  switch(item){
    case folder:
      return "Folder";
    case auton:
      return "Autonomous";
    case sSwitch:
      return "Setting";
    case sSlider:
      return "Setting";
  }
  return 0;
}

int currentItem = 0;


struct itemStruct {
  int parentItemNumber;
  int itemType;
  std::vector<int> items;
  const char *name;
  int settingValue;
};

/*===========================================================================*/


std::vector <itemStruct> Database = {
  ////////    p, --type--, ----------items--------, --------"name"--------, settingValue
  /*  0 */  { 0,   folder, {1,  2,  3,  4,  5,  6},   "root"},
  /*  1 */  { 0,    auton, {                     }, "auton1"},
  /*  2 */  { 0,    auton, {                     }, "auton2"},
  /*  3 */  { 0,    auton, {                     }, "auton3"},
  /*  4 */  { 0,    auton, {                     }, "auton4"},
  /*  5 */  { 0,    auton, {                     }, "auton5"},
  /*  6 */  { 0,   folder, {7, 8                 }, "Test folder"},
  /*  7 */  { 6,    auton, {                     }, "auton6"},
  /*  8 */  { 6,    auton, {                     }, "auton7"},
  /*  9 */  { 4 },
  /* 10 */  { 4 },
  /* 11 */  { 4 },
  /* 12 */  { 9 },
  /* 13 */  { 9 },
  /* 14 */  { 9 },
  /* 15 */  { 9 },
  /* 16 */  { 2 },
  /* 17 */  { 2 },
  /* 18 */  { 4 },
  ////////    p, b1, b2, b3, b4, --type--, -color-, --------"name"--------, ----------"description"----------,  swSt,  sP
};




class controllerMenu {
  public:
    // void runFunction ( int (controllerMenu::*function)() );
    
    void printMenu( void );

    int scrollLeft( void );
    int scrollRight( void );
    int select( void );
    int back( void );

    void setCallbacks( void );

  private:
    int cursorLocation;
    // void printMonospace (int, int, std::string );
    void printFolder( void );
    void printAuton( void );
    void printSettingSlider( void );
    void printSettingSwitch( void );
};

controllerMenu ControllerMenu;

// void controllerMenu::printMonospace (int row, int collumn, std::string stringIn ) {
//   for (int i = 0; i < stringIn.length(); i++) {
//     Controller1.Screen.setCursor(row, collumn + i);
//     std::string tempString;
//     tempString = stringIn[i];
//     Controller1.Screen.print(tempString.c_str());
//   }
// }
typedef int (controllerMenu::*controllerMenuFunction)();

controllerMenu* functionToRun;
//  int (controllerMenu::*function)() 
int runFunction() {
  ControllerMenu.scrollRight();
  return 0;
}

void controllerMenu::printFolder( void ) {
  std::string selection = "[_][_][_][_][_][_]";
  selection.resize(Database[currentItem].items.size() * 3);
  selection.replace((cursorLocation) * 3 + 1, 1,  "o");

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(selection.c_str());
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(itemTypeChar(Database[Database[currentItem].items[cursorLocation]].itemType));
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(Database[Database[currentItem].items[cursorLocation]].name);
}
void controllerMenu::printAuton( void ) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(Database[currentItem].name);
}
void controllerMenu::printSettingSlider( void ) {
  Controller1.Screen.print("sl");

}
void controllerMenu::printSettingSwitch( void ) {
  Controller1.Screen.print("sw");

}


void controllerMenu::printMenu( void ) {
  switch(Database[currentItem].itemType){
  case folder:
    printFolder();
  break;
  case auton:
    printAuton();
  break;
  case sSwitch:
    printSettingSlider();
  break;
  case sSlider:
    printSettingSwitch();
  }
}


int controllerMenu::scrollLeft( void ) {
  if (cursorLocation > 0)
    cursorLocation = cursorLocation - 1;
  else
    cursorLocation = Database[currentItem].items.size() - 1;
  ControllerMenu.printMenu();
  return 0;
}

int controllerMenu::scrollRight( void ) {
  if (cursorLocation < Database[currentItem].items.size() - 1)
    cursorLocation = cursorLocation + 1;
  else
    cursorLocation = 0;
  ControllerMenu.printMenu();
  return 0;
}

int controllerMenu::back( void ) {
  cursorLocation = 0;
  currentItem = Database[currentItem].parentItemNumber;
  ControllerMenu.printMenu();
  return 0;
}

int controllerMenu::select( void ) {
  if (Database[currentItem].itemType == folder) {
    currentItem = Database[currentItem].items[cursorLocation];
    cursorLocation = 0;
  ControllerMenu.printMenu();
  }
  return 0;
}

void controllerMenu::setCallbacks()
{
  buttonCallbacks = {
    {Controller1.ButtonRight, &menuThread, setVoidFunction( ControllerMenu.scrollRight() )},
    {Controller1.ButtonLeft,  &menuThread, setVoidFunction( ControllerMenu.scrollLeft() )},
    {Controller1.ButtonA,    &menuThread, setVoidFunction( ControllerMenu.select() )},
    {Controller1.ButtonB,  &menuThread, setVoidFunction( ControllerMenu.back() )},
  };
  // buttonCallbacks[0].function = setVoidFunction( ControllerMenu.scrollRight() );
  // menuThread = this->scrollRight
}

void pre_auton( void ) {
  Controller1.ButtonB.pressed(abortEverything);

  // Controller1.ButtonLeft.pressed(setVoidFunction( ControllerMenu.scrollLeft() ));
  // Controller1.ButtonRight.pressed(setVoidFunction( ControllerMenu.scrollRight() ));
  // Controller1.ButtonA.pressed(setVoidFunction( ControllerMenu.select() ));
  // Controller1.ButtonB.pressed(setVoidFunction( ControllerMenu.back() ));

    // menuLcdDraw();
    // controllerDraw();
    // Brain.Screen.pressed(menuLcdTouch);
}

void autonomous( void ) {

}

void usercontrol( void ) {
    setDriveButtonCallbacks();
  // ControllerMenu.setCallbacks();
  ControllerMenu.printMenu();
  while (1) {
    runButtons();
    task::sleep(10); //Sleep task for a short amount of time to prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  vexcodeInit();
  
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );

  //Run the pre-autonomous function.
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(1) {
    task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }    
}