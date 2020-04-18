#include "vex.h"

#include <bits/stdc++.h>

#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace ControllerMenu {

namespace {

enum menuItemType {Folder, Autonomous, SettingSwitch, SettingSlider, Action};

const char *itemTypeName(int item) {
  switch (item) {
  case Folder:
    return "Folder";
  case Autonomous:
    return "Autonomous";
  case SettingSwitch:
    return "Setting";
  case SettingSlider:
    return "Setting";
  case Action:
    return "Action";
  }
  return 0;
}

int currentItem(0);

struct itemStruct {
  int parentItemNumber;
  int itemType;
  std::vector<int> items;
  const char *name;
  const char *description;
  void (*function)();
  int settingDefault;

  int settingValue;
  int cursorLocation;
};
// 19 or less chars!!!
// 1234567890123456789
std::vector <itemStruct> Database = {
  ////// parent, ----type-----, ----------items--------, --------"name"-------
  ////////   ---"descrtiption"---, -----------function----------, ------"name"------
  /*  0 */  { 0, Folder,        {1,  2,  3,  4,  5, 11},     "Folder is Empty"},
  /*  1 */  { 0, Folder,        {6                    },                 "Red"},
  /*  2 */  { 0, Folder,        {7,  7,  7,  7,  7,  7},                "Blue"},
  /*  3 */  { 0, Folder,        {8                    },              "Skills"},
  /*  4 */  { 0, Folder,        {0                    },               "Other"},
  /*  5 */  { 0, Folder,        {9, 10                },            "Settings"},
  /*  6 */  { 1, Autonomous,    {0},             "Red one", "1234567890123456789", RobotFunctions::countDownTask},
  /*  7 */  { 2, Autonomous,    {0},            "Blue one",                  "Scores points", RobotFunctions::countDownTask},
  /*  8 */  { 3, Autonomous,    {0},          "Skills one",                  "Scores points", RobotFunctions::countDownTask},
  /*  9 */  { 5, SettingSlider, {0},              "Slider",             "", NULL, 57},
  /* 10 */  { 5, SettingSwitch, {0},              "Switch",             "", NULL, 1},
  /* 11 */  { 0, Folder,        {12, 13, 14           },             "Actions"},
  /* 12 */  {11, Action,        {0},      "Reset defaults",             "", resetSettingDefaults},
  /* 13 */  {11, Action,        {0},      "Store Settings",             "", storeSettings},
  /* 14 */  {11, Action,        {0},       "Load Settings",             "", loadSettings},
  /* 15 */  
  /* 16 */  
  /* 17 */  
  /* 18 */  
};


const char *intToConstCharP(int input) {
  std::stringstream str;
  str << input;
  const char *output = str.str().c_str();
  return output;
}

void printFolder() {
  std::string selection = "[_][_][_][_][_][_]";
  selection.resize(Database[currentItem].items.size() * 3);
  selection.replace((Database[currentItem].cursorLocation) * 3 + 1, 1, "o");

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(selection.c_str());
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(itemTypeName(Database[Database[currentItem].items
                           [Database[currentItem].cursorLocation]].itemType));    
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(Database[Database[currentItem].items
                           [Database[currentItem].cursorLocation]].name);
}

void printAuton() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(Database[currentItem].name);
}

void printSettingSlider() {
  std::string bar = "l.................l";
  int barValue = Database[currentItem].settingValue * 0.17;
  bar.replace(1, barValue, barValue, '!');

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(Database[currentItem].name);
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(bar.c_str());
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print("%d%%", Database[currentItem].settingValue);
}

void printSettingSwitch() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(Database[currentItem].name);
  Controller1.Screen.setCursor(2, 0);
  if (Database[currentItem].settingValue) {
    Controller1.Screen.print("True");
  } else {
    Controller1.Screen.print("False");
  }
}

void printAction(const char *message) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(Database[currentItem].name);
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(Database[currentItem].description);
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(message);
}

void scroll(int direction) {
  switch (Database[currentItem].itemType) {
    int tempCursorLocation;
    int tempSettingValue;
  case Folder:
    tempCursorLocation = Database[currentItem].cursorLocation + direction;
    if (tempCursorLocation < 0) {
      tempCursorLocation = Database[currentItem].items.size() - 1;
    } else if (tempCursorLocation > Database[currentItem].items.size() - 1) {
      tempCursorLocation = 0;
    }

    Database[currentItem].cursorLocation = tempCursorLocation;
    break;
  case SettingSlider:
    tempSettingValue = Database[currentItem].settingValue + direction;
    if (Database[currentItem].settingValue + direction < 0) {
      tempSettingValue = 0;
    } else if (Database[currentItem].settingValue + direction > 100) {
      tempSettingValue = 100;
    }
    Database[currentItem].settingValue = tempSettingValue;
    break;
  }
  printMenu();
}

void scrollRight() { scroll(1); }

void scrollLeft() { scroll(-1); }

void scrollUp() { scroll(10); }

void scrollDown() { scroll(-10); }

void back() {
  currentItem = Database[currentItem].parentItemNumber;
  printMenu();
}

void select() {
  switch (Database[currentItem].itemType) {
  case Folder:
    currentItem = Database[currentItem].items[Database[currentItem].cursorLocation];
    printMenu();
    break;
  case SettingSwitch:
    Database[currentItem].settingValue = !Database[currentItem].settingValue;
    printMenu();
    break;
  case Action:
    printAction("Running...");
    Database[currentItem].function();
    printAction("Complete!");
    Controller1.rumble(".");
    break;
  }
}
} // namespace

void printMenu() {
  switch (Database[currentItem].itemType) {
  case Folder:
    printFolder();
    break;
  case Autonomous:
    printAuton();
    break;
  case SettingSwitch:
    printSettingSwitch();
    break;
  case SettingSlider:
    printSettingSlider();
    break;
  case Action:
    printAction("Press 'A' to run");
    break;
  }
}

void setCallbacks() {
  using namespace ControllerButtons;
  buttonCallbacks = {
    {Controller1.ButtonRight, false, &Group::menu, 0, scrollRight},
    {Controller1.ButtonLeft,  false, &Group::menu, 0, scrollLeft},
    {Controller1.ButtonUp,    false, &Group::menu, 0, scrollUp},
    {Controller1.ButtonDown,  false, &Group::menu, 0, scrollDown},
    {Controller1.ButtonA,     false, &Group::menu, 0, select},
    {Controller1.ButtonB,     false, &Group::menu, 0, back},
  };
}

void runAuton() {
  if (Database[currentItem].itemType == Autonomous) {
    Controller1.rumble(".");
    Database[currentItem].function();
  }
}

void checkForAuton() {
  if (Database[currentItem].itemType != Autonomous) {
    Controller1.rumble(".");
  }
}

void resetSettingDefaults() {
  for (int i = 0; i < Database.size(); i++) {
    if (Database[i].itemType == SettingSlider ||
        Database[i].itemType == SettingSwitch) {
      uint8_t dataIn = Database[i].settingDefault;
      Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
    }
  }
}

void loadSettings() {
  for (int i = 0; i < Database.size(); i++) {
    if (Database[i].itemType == SettingSlider ||
        Database[i].itemType == SettingSwitch) {
      uint8_t dataIn;
      Brain.SDcard.loadfile(intToConstCharP(i), &dataIn, 3);
      int dataOut = dataIn;
      Database[i].settingValue = dataOut;
    }
  }
}

void storeSettings() {
  for (int i = 0; i < Database.size(); i++) {
    if (Database[i].itemType == SettingSlider ||
        Database[i].itemType == SettingSwitch) {
      uint8_t dataIn = Database[i].settingValue;
      Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
    }
  }
}

} // namespace ControllerMenu