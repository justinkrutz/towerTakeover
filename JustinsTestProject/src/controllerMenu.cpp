#include "vex.h"

#include <bits/stdc++.h>

#include "controllerMenu.h"
#include "robotFunctions.h" 

using namespace vex;

controllerMenu ControllerMenu;

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


void controllerMenu::scrollLeft( void ) {
  if (cursorLocation > 0)
    cursorLocation = cursorLocation - 1;
  else
    cursorLocation = Database[currentItem].items.size() - 1;
  ControllerMenu.printMenu();
}

void controllerMenu::scrollRight( void ) {
  if (cursorLocation < Database[currentItem].items.size() - 1)
    cursorLocation = cursorLocation + 1;
  else
    cursorLocation = 0;
  ControllerMenu.printMenu();
}

void controllerMenu::back( void ) {
  cursorLocation = 0;
  currentItem = Database[currentItem].parentItemNumber;
  ControllerMenu.printMenu();
}

void controllerMenu::select( void ) {
  if (Database[currentItem].itemType == folder) {
    currentItem = Database[currentItem].items[cursorLocation];
    cursorLocation = 0;
  ControllerMenu.printMenu();
  }
}

