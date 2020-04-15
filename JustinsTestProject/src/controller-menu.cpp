#include "vex.h"

#include <bits/stdc++.h>

#include "controller-menu.h"
#include "controller-buttons.h"
#include "robot-functions.h" 

using namespace vex;

namespace ControllerMenu {

  // Members only accessible within namespace ControllerMenu
  /*===========================================================================*/
  namespace {
    const char *itemTypeName(int item) {
      switch(item){
        case FOLDER:
          return "Folder";
        case AUTON:
          return "Autonomous";
        case SETTING_SWITCH:
          return "Setting";
        case SETTING_SLIDER:
          return "Setting";
        case ACTION:
          return "Action";
      }
      return 0;
    }

    int currentItem (0);

    struct itemStruct {
      int parentItemNumber;
      int itemType;
      std::vector<int> items;
      const char *name;
      const char *description;
      void (* function)();
      int settingDefault;

      int settingValue;
      int cursorLocation;
    };


    std::vector <itemStruct> Database = {
      ////////    p, --type--, ----------items--------, --------"name"--------, settingValue
      /*  0 */  { 0,         FOLDER, {1,  2,  3,  4,  5, 11},   "Folder is Empty",                                "", },
      /*  1 */  { 0,         FOLDER, {6                    },               "Red",                                "", },
      /*  2 */  { 0,         FOLDER, {7,  7,  7,  7,  7,  7},              "Blue",                                "", },
      /*  3 */  { 0,         FOLDER, {8                    },            "Skills",                                "", },
      /*  4 */  { 0,         FOLDER, {0                    },             "Other",                                "", },
      /*  5 */  { 0,         FOLDER, {9, 10                },          "Settings",                                "", },
      /*  6 */  { 1,          AUTON, {0                    },           "Red one",                                "", RobotFunctions::countDownTask},
      /*  7 */  { 2,          AUTON, {0                    },          "Blue one",                                "", RobotFunctions::countDownTask},
      /*  8 */  { 3,          AUTON, {0                    },        "Skills one",                                "", RobotFunctions::countDownTask},
      /*  9 */  { 5, SETTING_SLIDER, {0                    },            "Slider",                                "", NULL, 57},
      /* 10 */  { 5, SETTING_SWITCH, {0                    },            "Switch",                                "", NULL, 1},
      /* 11 */  { 0,         FOLDER, {12, 13, 14           },           "Actions",                                "", },
      /* 12 */  { 11,        ACTION, {0                    },    "Reset defaults",                                "", resetSettingDefaults},
      /* 13 */  { 11,        ACTION, {0                    },    "Store Settings",                                "", storeSettings},
      /* 14 */  { 11,        ACTION, {0                    },     "Load Settings",                                "", loadSettings},
      /* 15 */  
      /* 16 */  
      /* 17 */  
      /* 18 */  
      ////////    p, b1, b2, b3, b4, --type--, -color-, --------"name"--------, ----------"description"----------,  swSt,  sP
    };

    const char * intToConstCharP (int input) {
      std::stringstream str;
      str << input;
      const char * output = str.str().c_str();
      return output;
    }

    void printFolder() {
      std::string selection = "[_][_][_][_][_][_]";
      selection.resize(Database[currentItem].items.size() * 3);
      selection.replace((Database[currentItem].cursorLocation) * 3 + 1, 1,  "o");

      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 0);
      Controller1.Screen.print(selection.c_str());
      Controller1.Screen.setCursor(2, 0);
      Controller1.Screen.print(itemTypeName(Database[Database[currentItem].items[Database[currentItem].cursorLocation]].itemType));
      Controller1.Screen.setCursor(3, 0);
      Controller1.Screen.print(Database[Database[currentItem].items[Database[currentItem].cursorLocation]].name);
    }

    void printAuton() {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 0);
      Controller1.Screen.print(Database[currentItem].name);
    }

    void printSettingSlider() {
      std::string bar = "l.................l";
      int barValue = Database[currentItem].settingValue * 0.17;
      bar.replace(1, barValue, barValue,  '!');
      // empty.assign((100 - Database[currentItem].settingValue) * 0.17, '.');
      // bar.resize(Database[currentItem].items.size() * 3);
      // selection.replace((Database[currentItem].cursorLocation) * 3 + 1, 1,  std::string::assign(1, "|"));

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
      if(Database[currentItem].settingValue){
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
        case FOLDER:
          tempCursorLocation = Database[currentItem].cursorLocation + direction;
          if (tempCursorLocation < 0){
            tempCursorLocation = Database[currentItem].items.size() - 1;
          } else if (tempCursorLocation > Database[currentItem].items.size() - 1){
            tempCursorLocation = 0;
          }

          Database[currentItem].cursorLocation = tempCursorLocation;
        break;
        case SETTING_SLIDER:
          tempSettingValue = Database[currentItem].settingValue + direction;
          if (Database[currentItem].settingValue + direction < 0){
            tempSettingValue = 0;
          } else if (Database[currentItem].settingValue + direction > 100){
            tempSettingValue = 100;
          }
          Database[currentItem].settingValue = tempSettingValue;
        break;
      }
      printMenu();
    }

    void scrollRight() {
      scroll(1);
    }

    void scrollLeft() {
      scroll(-1);
    }

    void scrollUp() {
      scroll(10);
    }

    void scrollDown() {
      scroll(-10);
    }

    void back() {
      currentItem = Database[currentItem].parentItemNumber;
      printMenu();
    }

    void select() {
      switch (Database[currentItem].itemType) {
        case FOLDER:
          Database[currentItem].cursorLocation = Database[currentItem].cursorLocation;
          currentItem = Database[currentItem].items[Database[currentItem].cursorLocation];
          printMenu();
        break;
        case SETTING_SWITCH:
          Database[currentItem].settingValue = !Database[currentItem].settingValue;
          printMenu();
        break;
        case ACTION:
          printAction("Running...");
          Database[currentItem].function();
          printAction("Complete!");
          Controller1.rumble(".");
        break;
      }
    }
  }

  // Public members in namespace ControllerMenu
  /*===========================================================================*/
  void printMenu() {
    switch(Database[currentItem].itemType){
    case FOLDER:
      printFolder();
    break;
    case AUTON:
      printAuton();
    break;
    case SETTING_SWITCH:
      printSettingSwitch();
    break;
    case SETTING_SLIDER:
      printSettingSlider();
    break;
    case ACTION:
      printAction("Press 'A' to run");
    break;
    }
  }

  void setCallbacks() {
    ControllerButtons::buttonCallbacks = {
      {Controller1.ButtonRight, false, &ControllerButtons::Group::menu, 0, scrollRight},
      {Controller1.ButtonLeft,  false, &ControllerButtons::Group::menu, 0, scrollLeft},
      {Controller1.ButtonUp,    false, &ControllerButtons::Group::menu, 0, scrollUp},
      {Controller1.ButtonDown,  false, &ControllerButtons::Group::menu, 0, scrollDown},
      {Controller1.ButtonA,     false, &ControllerButtons::Group::menu, 0, select},
      {Controller1.ButtonB,     false, &ControllerButtons::Group::menu, 0, back},
    };
  }

  void runAuton() {
    if (Database[currentItem].itemType == AUTON){
      Controller1.rumble(".");
      Database[currentItem].function();
    }
  }

  void checkForAuton() {
    if (Database[currentItem].itemType != AUTON) {
      Controller1.rumble(".");
    }
  }

  void resetSettingDefaults() {
    for (int i = 0; i < Database.size(); i++) {
      if (Database[i].itemType == SETTING_SLIDER || Database[i].itemType == SETTING_SWITCH) {
        uint8_t dataIn = Database[i].settingDefault;
        Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
      }
    }
  }

  void loadSettings() {
    for (int i = 0; i < Database.size(); i++) {
      if (Database[i].itemType == SETTING_SLIDER || Database[i].itemType == SETTING_SWITCH) {
        uint8_t dataIn;
        Brain.SDcard.loadfile(intToConstCharP(i), &dataIn, 3);
        int dataOut = dataIn;
        Database[i].settingValue = dataOut;
      }
    }
  }

  void storeSettings() {
    for (int i = 0; i < Database.size(); i++) {
      if (Database[i].itemType == SETTING_SLIDER || Database[i].itemType == SETTING_SWITCH) {
        uint8_t dataIn = Database[i].settingValue;
        Brain.SDcard.savefile(intToConstCharP(i), &dataIn, 3);
      }
    }
  }

}