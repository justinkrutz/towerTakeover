#include "vex.h"

#include <bits/stdc++.h>

#include "controller-buttons.h"
#include "controller-menu.h"
#include "robot-functions.h"

using namespace vex;

namespace ControllerMenu {

namespace {

enum itemTypeEnum {Folder, Autonomous, Toggle, Slider, Action};

const char *itemTypeName(int item) {
  switch (item) {
  case Folder:
    return "Folder";
  case Autonomous:
    return "Autonomous";
  case Toggle:
    return "Setting";
  case Slider:
    return "Setting";
  case Action:
    return "Action";
  }
  return 0;
}


struct ItemStruct {
  itemTypeEnum itemType;
  const char *name;
  ItemStruct *parentItem;

  std::vector<ItemStruct *> items;
  int cursorLocation;

  void (*function)();
  const char *description;

  int settingDefaultValue;
  int settingCurrentValue;
};

std::vector<ItemStruct *> settingList;

ItemStruct *currentItem;


ItemStruct createFolderItem(const char *name, std::vector<ItemStruct *> items) {
  ItemStruct tempStruct;
  tempStruct.cursorLocation = 0;
  tempStruct.itemType = Folder;
  tempStruct.name = name;
  tempStruct.items = items;
  return tempStruct;
}

ItemStruct createAutonItem(const char *name, void (*function)(), const char *description) {
  ItemStruct tempStruct;
  tempStruct.itemType = Autonomous;
  tempStruct.name = name;
  tempStruct.function = function;
  tempStruct.description = description;
  return tempStruct;
}

ItemStruct createToggleItem(const char *name, int settingDefaultValue, const char *description) {
  ItemStruct tempStruct;
  tempStruct.itemType = Toggle;
  tempStruct.name = name;
  tempStruct.settingDefaultValue = settingDefaultValue;
  return tempStruct;
}

ItemStruct createSliderItem(const char *name, int settingDefaultValue, const char *description) {
  ItemStruct tempStruct;
  tempStruct.itemType = Slider;
  tempStruct.name = name;
  tempStruct.settingDefaultValue = settingDefaultValue;
  return tempStruct;
}

ItemStruct createActionItem(const char *name, void (*function)(), const char *description) {
  ItemStruct tempStruct;
  tempStruct.itemType = Action;
  tempStruct.name = name;
  tempStruct.function = function;
  tempStruct.description = description;
  return tempStruct;
}


// ItemStruct redAutonOne {Autonomous, "Red One", {}, {RobotFunctions::countUpTask}};
// ItemStruct root {Folder, "Folder is empty", {{redAutonOne}}};s



// 19 or less chars!!!
// 1234567890123456789
// std::vector <ItemStruct> settingList = {
//   ////// parent, ----type-----, ----------items--------, --------"name"-------
//   ////////   ---"descrtiption"---, -----------function----------, ------"name"------
//   /*  0 */  { 0, Folder,        {1,  2,  3,  4,  5, 11},     "Folder is Empty"},
//   /*  1 */  { 0, Folder,        {6                    },                 "Red"},
//   /*  2 */  { 0, Folder,        {7,  7,  7,  7,  7,  7},                "Blue"},
//   /*  3 */  { 0, Folder,        {8                    },              "Skills"},
//   /*  4 */  { 0, Folder,        {0                    },               "Other"},
//   /*  5 */  { 0, Folder,        {9, 10                },            "Settings"},
//   /*  6 */  { 1, Autonomous,    {0},             "Red one", "1234567890123456789", RobotFunctions::countDownTask},
//   /*  7 */  { 2, Autonomous,    {0},            "Blue one",                  "Scores points", RobotFunctions::countDownTask},
//   /*  8 */  { 3, Autonomous,    {0},          "Skills one",                  "Scores points", RobotFunctions::countDownTask},
//   /*  9 */  { 5, Slider, {0},              "Slider",             "", NULL, 57},
//   /* 10 */  { 5, Toggle, {0},              "Switch",             "", NULL, 1},
//   /* 11 */  { 0, Folder,        {12, 13, 14           },             "Actions"},
//   /* 12 */  {11, Action,        {0},      "Reset defaults",             "", resetSettingDefaults},
//   /* 13 */  {11, Action,        {0},      "Store Settings",             "", storeSettings},
//   /* 14 */  {11, Action,        {0},       "Load Settings",             "", loadSettings},
//   /* 15 */  
//   /* 16 */  
//   /* 17 */  
//   /* 18 */  
// };


const char *intToConstCharP(int input) {
  std::stringstream str;
  str << input;
  const char *output = str.str().c_str();
  return output;
}

void printFolder() {
  std::string selection = "[_][_][_][_][_][_]";
  selection.resize(currentItem->items.size() * 3);
  selection.replace((currentItem->cursorLocation) * 3 + 1, 1, "o");

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(selection.c_str());
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(itemTypeName(currentItem->items
                           [currentItem->cursorLocation]->itemType));    
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(currentItem->items[currentItem->cursorLocation]->name);
}

void printAuton() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(currentItem->name);
}

void printSlider() {
  std::string bar = "l.................l";
  int barValue = currentItem->settingCurrentValue * 0.17;
  bar.replace(1, barValue, barValue, '!');

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(currentItem->name);
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(bar.c_str());
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print("%d%%", currentItem->settingCurrentValue);
}

void printToggle() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(currentItem->name);
  Controller1.Screen.setCursor(2, 0);
  if (currentItem->settingCurrentValue) {
    Controller1.Screen.print("True");
  } else {
    Controller1.Screen.print("False");
  }
}

void printAction(const char *message) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print(currentItem->name);
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print(currentItem->description);
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(message);
}

void scroll(int direction) {
  switch (currentItem->itemType) {
    int tempCursorLocation;
    int tempsettingCurrentValue;
  case Folder:
    tempCursorLocation = currentItem->cursorLocation + direction;
    if (tempCursorLocation < 0) {
      tempCursorLocation = currentItem->items.size() - 1;
    } else if (tempCursorLocation > currentItem->items.size() - 1) {
      tempCursorLocation = 0;
    }

    currentItem->cursorLocation = tempCursorLocation;
    break;
  case Slider:
    tempsettingCurrentValue = currentItem->settingCurrentValue + direction;
    if (currentItem->settingCurrentValue + direction < 0) {
      tempsettingCurrentValue = 0;
    } else if (currentItem->settingCurrentValue + direction > 100) {
      tempsettingCurrentValue = 100;
    }
    currentItem->settingCurrentValue = tempsettingCurrentValue;
    break;
  }
  printMenu();
}

void scrollRight() { scroll(1); }

void scrollLeft() { scroll(-1); }

void scrollUp() { scroll(10); }

void scrollDown() { scroll(-10); }

void back() {
  currentItem = currentItem->parentItem;
  printMenu();
}

void select() {
  switch (currentItem->itemType) {
  case Folder:
      currentItem->items[currentItem->cursorLocation]->parentItem = currentItem;
      currentItem = currentItem->items[currentItem->cursorLocation];
    printMenu();
    break;
  case Toggle:
    currentItem->settingCurrentValue = !currentItem->settingCurrentValue;
    printMenu();
    break;
  case Action:
    printAction("Running...");
    currentItem->function();
    printAction("Complete!");
    Controller1.rumble(".");
    break;
  }
}
} // namespace

void printMenu() {
  switch (currentItem->itemType) {
  case Folder:
    printFolder();
    break;
  case Autonomous:
    printAuton();
    break;
  case Toggle:
    printToggle();
    break;
  case Slider:
    printSlider();
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
  if (currentItem->itemType == Autonomous) {
    Controller1.rumble(".");
    currentItem->function();
  }
}

void checkForAuton() {
  if (currentItem->itemType != Autonomous) {
    Controller1.rumble(".");
  }
}

void loadSettings() {
  for (int i = 0; i < settingList.size(); i++) {
    if (settingList[i]->itemType == Slider ||
        settingList[i]->itemType == Toggle) {
      uint8_t dataIn;
      Brain.SDcard.loadfile(intToConstCharP(i), &dataIn, 3);
      int dataOut = dataIn;
      settingList[i]->settingCurrentValue = dataOut;
    }
  }
}

void storeSettings() {
  for (int i = 0; i < settingList.size(); i++) {
    if (settingList[i]->itemType == Slider ||
        settingList[i]->itemType == Toggle) {
      uint8_t dataIn = settingList[i]->settingCurrentValue;
      Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
    }
  }
}

void resetSettingDefaults() {
  for (int i = 0; i < settingList.size(); i++) {
    if (settingList[i]->itemType == Slider ||
        settingList[i]->itemType == Toggle) {
      uint8_t dataIn = settingList[i]->settingDefaultValue;
      Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
    }
  }
}

ItemStruct redAutonOneI = createAutonItem(
    "Red One", RobotFunctions::countUpTask, "Hopefully scores");
ItemStruct blueAutonOneI = createAutonItem(
    "Blue One", RobotFunctions::countUpTask, "Hopefully scores");
ItemStruct skillsAutonOneI = createAutonItem(
    "Skills One", RobotFunctions::countUpTask, "Hopefully scores");
ItemStruct testSliderI = createSliderItem(
    "Test Slider", 64, "Words");
ItemStruct testToggleI = createToggleItem(
    "Test Toggle", 1, "Word");
ItemStruct loadSettingsI = createActionItem(
    "Load Settings", loadSettings, "from SD card");
ItemStruct storeSettingsI = createActionItem(
    "Store Settings", storeSettings, "to SD card");
ItemStruct resetSettingDefaultsI = createActionItem(
    "Reset Defaults", resetSettingDefaults, "from program");

ItemStruct actions  = createFolderItem("Actions",  {&loadSettingsI,
                                                    &storeSettingsI,
                                                    &resetSettingDefaultsI});
ItemStruct settings = createFolderItem("Settings", {&testSliderI,
                                                    &testToggleI});
ItemStruct other    = createFolderItem("Other",    {});
ItemStruct skills   = createFolderItem("Skills",   {&skillsAutonOneI});
ItemStruct blue     = createFolderItem("Blue",     {&blueAutonOneI,
                                                    &blueAutonOneI,
                                                    &blueAutonOneI});
ItemStruct red      = createFolderItem("Red",      {&redAutonOneI});

ItemStruct root     = createFolderItem("Root",     {&red, 
                                                    &blue,
                                                    &skills,
                                                    &other, 
                                                    &settings,
                                                    &actions});
void menuItemInit() {
  currentItem = &root;
}

} // namespace ControllerMenu