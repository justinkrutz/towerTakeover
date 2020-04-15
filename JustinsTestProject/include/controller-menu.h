#define FOLDER 0
#define AUTON 1
#define SETTING_SWITCH 2
#define SETTING_SLIDER 3
#define ACTION 4

namespace ControllerMenu {
  extern void printMenu();
  extern void setCallbacks();
  extern void runAuton();
  extern void checkForAuton();
  extern void resetSettingDefaults();
  extern void storeSettings();
  extern void loadSettings();
}