#include "vex.h"
using namespace vex;
vex::brain Brain;
vex::controller Controller;

//Menu
  #define green color(0x00ff00)
  #define red color(0xFF0000)
  #define blue color(0x0000FF)
  #define yellow color(0xFFFF00)
  #define fontColor color(white)
  #define iconOutlineColor color(white)
  #define backgroundColor color(0x666666)
  #define buttonColor color(0x191919)
  #define pathColor color(0x2F3136)

  #define folder 0
  #define auton 1
  #define sSwitch 2
  #define sSlider 3



  // void sdCard() {
  //   if (Brain.SDcard.isInserted()) {

  //   }
  //   else
  // }


  bool screenPressed = false;
  // bool edgeTrigger = Brain.Screen.pressing() && !screenPressed;
  int currentMenu = 0;
  int currentPage = 0;
  struct Page {
    int parentPageNumber;
    int buttonOnePageNumber;
    int buttonTwoPageNumber;
    int buttonThreePageNumber;
    int buttonFourPageNumber;
    int pageType;
    color pageColor;
    const char *name;
    const char *description;
    bool switchState;
    int sliderPct;
  };
  Page pages[41] = {
  ////////    p, b1, b2, b3, b4,    type,  color,                "name",                    "description",  swSt,  sP
  /*  0 */  { 0,  1,  2,  3,  4,  folder, __null,                    ""},
  /*  1 */  { 0, 12,  5,  0,  0,  folder,    red,                 "Red"},
  /*  2 */  { 0, 26, 19,  0,  0,  folder,   blue,                "Blue"},
  /*  3 */  { 0, 33,  0,  0,  0,  folder, yellow,              "Skills"},
  /*  4 */  { 0, 34, 35, 36,  0,  folder,  green,               "Other"},
  /*  5 */  { 1,  6,  9,  0,  0,  folder,    red,                "Back"},
  /*  6 */  { 5,  7,  8,  0,  0,  folder,    red,             "Parking"},
  /*  7 */  { 6,  0,  0,  0,  0,   auton,    red,       "3 flags 1 cap",      "(insert description here)"},  
  /*  8 */  { 6,  0,  0,  0,  0,   auton,    red,     "5 flags no caps",      "(insert description here)"},
  /*  9 */  { 5, 10, 11,  0,  0,  folder,    red,         "Non-Parking"},
  /* 10 */  { 9,  0,  0,  0,  0,   auton,    red,       "3 flags 1 cap",      "(insert description here)"},
  /* 11 */  { 9,  0,  0,  0,  0,   auton,    red,     "5 flags no caps",      "(insert description here)"},
  /* 12 */  { 1, 13, 16,  0,  0,  folder,    red,               "Front"},
  /* 13 */  {12, 14, 15,  0,  0,  folder,    red,             "Parking"},
  /* 14 */  {13,  0,  0,  0,  0,   auton,    red,       "3 flags 1 cap",      "(insert description here)"},  
  /* 15 */  {13,  0,  0,  0,  0,   auton,    red,     "5 flags no caps",      "(insert description here)"},
  /* 16 */  {12, 17, 18,  0,  0,  folder,    red,         "Non-Parking"},
  /* 17 */  {16,  0,  0,  0,  0,   auton,    red,       "3 flags 1 cap",      "(insert description here)"},  
  /* 18 */  {16,  0,  0,  0,  0,   auton,    red,     "5 flags no caps",      "(insert description here)"},
  /* 19 */  { 2, 20, 23,  0,  0,  folder,   blue,                "Back"},
  /* 20 */  {19, 21, 22,  0,  0,  folder,   blue,             "Parking"},
  /* 21 */  {20,  0,  0,  0,  0,   auton,   blue,       "3 flags 1 cap",      "(insert description here)"},  
  /* 22 */  {20,  0,  0,  0,  0,   auton,   blue,     "5 flags no caps",      "(insert description here)"},
  /* 23 */  {19, 24, 25,  0,  0,  folder,   blue,         "Non-Parking"},
  /* 24 */  {23,  0, 0,   0,  0,   auton,   blue,       "3 flags 1 cap",      "(insert description here)"},  
  /* 25 */  {23,  0,  0,  0,  0,   auton,   blue,     "5 flags no caps",      "(insert description here)"},
  /* 26 */  { 2, 27, 30,  0,  0,  folder,   blue,               "Front"},
  /* 27 */  {26, 28, 29,  0,  0,  folder,   blue,             "Parking"},
  /* 28 */  {27,  0,  0,  0,  0,   auton,   blue,       "3 flags 1 cap",      "(insert description here)"},  
  /* 29 */  {27,  0,  0,  0,  0,   auton,   blue,     "5 flags no caps",      "(insert description here)"},
  /* 30 */  {26, 31, 32,  0,  0,  folder,   blue,         "Non-Parking"},
  /* 31 */  {30,  0,  0,  0,  0,   auton,   blue,       "3 flags 1 cap",      "(insert description here)"},  
  /* 32 */  {30,  0,  0,  0,  0,   auton,   blue,     "5 flags no caps",      "(insert description here)"},
  /* 33 */  { 3,  0,  0,  0,  0,   auton, yellow,          "Skills one",             "Does skills stuff."},
  /* 34 */  { 4, 37, 38, 39, 40,  folder,  green,            "Settings"},
  /* 35 */  { 4,  0,  0,  0,  0,   auton,  green,                "None",                  "Does nothing."},
  /* 36 */  { 4,  0,  0,  0,  0,   auton,  green, "Random test program",                "Self destructs."},
  /* 37 */  {34,  0,  0,  0,  0, sSlider,  green,      "Useless slider",                    "Is useless.", false,  57},
  /* 38 */  {34,  0,  0,  0,  0, sSwitch,  green,       "Self destruct", "Toggles self dectruct feature.",  true},
  /* 39 */  {34,  0,  0,  0,  0, sSwitch,  green,                 "Win",         "Toggles match outcome.", false},
  /* 40 */  {34,  0,  0,  0,  0, sSwitch,  green,              "Flight",        "Toggles ability to fly.", false},
  ////////    p, b1, b2, b3, b4,    type,  color,                "name",                    "description",  swSt,  sP
  };

  void menuDrawIcon(int iconX, int iconY, int iconType, color iconColor) {
    Brain.Screen.setPenColor(iconOutlineColor);
    Brain.Screen.setPenWidth(0);
    if (iconType == folder) { // File
      Brain.Screen.drawRectangle(4+iconX, 4+iconY, 32, 12, iconColor);
      Brain.Screen.setPenWidth(4);
      Brain.Screen.drawLine(0+iconX, 2+iconY, 18+iconX, 2+iconY);
      Brain.Screen.drawLine(17+iconX, 2+iconY, 21+iconX, 6+iconY);
      Brain.Screen.drawLine(19+iconX, 6+iconY, 39+iconX, 6+iconY);
      Brain.Screen.drawLine(38+iconX, 4+iconY, 38+iconX, 39+iconY);
      Brain.Screen.drawLine(0+iconX, 38+iconY, 39+iconX, 38+iconY);
      Brain.Screen.drawLine(2+iconX, 39+iconY, 2+iconX, 0+iconY);
      Brain.Screen.drawLine(0+iconX, 18+iconY, 17+iconX, 18+iconY);
      Brain.Screen.drawLine(16+iconX, 18+iconY, 20+iconX, 14+iconY);
      Brain.Screen.drawLine(19+iconX, 14+iconY, 39+iconX, 14+iconY);
    } else if (iconType == auton) { // Folder
      Brain.Screen.drawRectangle(7+iconX, 4+iconY, 15, 32, iconColor);
      Brain.Screen.drawRectangle(22+iconX, 15+iconY, 11, 21, iconColor);
      Brain.Screen.setPenWidth(4);
      Brain.Screen.drawLine(3+iconX, 2+iconY, 26+iconX, 2+iconY);
      Brain.Screen.drawLine(5+iconX, 0+iconY, 5+iconX, 39+iconY);
      Brain.Screen.drawLine(3+iconX, 38+iconY, 36+iconX, 38+iconY);
      Brain.Screen.drawLine(35+iconX, 10+iconY, 35+iconX, 39+iconY);
      Brain.Screen.drawLine(24+iconX, 1+iconY, 34+iconX, 11+iconY);
      Brain.Screen.drawLine(24+iconX, 2+iconY, 24+iconX, 14+iconY);
      Brain.Screen.drawLine(22+iconX, 13+iconY, 36+iconX, 13+iconY);
      Brain.Screen.drawLine(10+iconX, 11+iconY, 19+iconX, 11+iconY);
      Brain.Screen.drawLine(10+iconX, 20+iconY, 30+iconX, 20+iconY);
      Brain.Screen.drawLine(10+iconX, 29+iconY, 30+iconX, 29+iconY);
    } else if (iconType == sSwitch || sSlider){
      Brain.Screen.drawImageFromFile("iconSettings.png", 0+iconX, 0+iconY);
    }
  }

  void menuNavBar(int pathPosition, bool iconClose) {
    std::string pathText("");
    if (pathPosition == 0) pathText = "/";
    else {
      while(pathPosition != 0){
      pathText = "/" + std::string(pages[pathPosition].name) + pathText;
      pathPosition = pages[pathPosition].parentPageNumber;
      }
    }
    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle(0, 0, 50, 32, color(buttonColor)); // Draw up button
    Brain.Screen.drawRectangle(430, 0, 50, 32, color(buttonColor)); // Draw home button
    Brain.Screen.drawRectangle(60, 0, 360, 32, color(pathColor)); // Draw path button
    Brain.Screen.setPenColor(fontColor); // Set text color
    Brain.Screen.setFont(fontType::prop20);
    Brain.Screen.printAt(68, 22, false, pathText.c_str()); // Print path button text
    if (iconClose) Brain.Screen.drawImageFromFile("iconClose.png", 9, 0);
    else Brain.Screen.drawImageFromFile("iconUp.png", 9, 0);
    Brain.Screen.drawImageFromFile("iconHome.png", 439, 0);
  }

  void menuButton(int buttonNumber, int buttonPageNumber) {
  if (buttonPageNumber != 0) {
      Brain.Screen.setPenWidth(0); // Remove outline
      Brain.Screen.drawRectangle(60, 42+50*(buttonNumber-1), 411, 40, color(buttonColor)); // Draw button
      
      menuDrawIcon(10, 42+50*(buttonNumber-1), pages[buttonPageNumber].pageType, pages[buttonPageNumber].pageColor);

      Brain.Screen.setPenColor(fontColor); // Set text color
      Brain.Screen.setFont(fontType::prop30);
      Brain.Screen.printAt(68, 72+50*(buttonNumber-1), false, pages[buttonPageNumber].name);
    }
  }

  void menuFolder() {
    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle(0, 0, 480, 240, color(backgroundColor)); // Draw background

    menuNavBar(currentPage, false);

    menuButton(1, pages[currentPage].buttonOnePageNumber); // Print button one
    menuButton(2, pages[currentPage].buttonTwoPageNumber); // Print button two
    menuButton(3, pages[currentPage].buttonThreePageNumber); // Print button three
    menuButton(4, pages[currentPage].buttonFourPageNumber); // Print button four
  }

  void menuAuton() {
    menuButton(1, currentPage);
    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle(10, 92, 460, 140, color(buttonColor));
    Brain.Screen.setFont(fontType::prop20);
    Brain.Screen.printAt(20, 115, false, pages[currentPage].description);
    menuNavBar(pages[currentPage].parentPageNumber, true);
  }

  void menusSwitch() {
    menuFolder();
    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle(10, 142, 460, 90, color(buttonColor));
    menuButton(1, currentPage);
    Brain.Screen.setFont(fontType::prop20);
    Brain.Screen.printAt(20, 165, false, pages[currentPage].description);
    menuNavBar(pages[currentPage].parentPageNumber, true);
    if (pages[currentPage].switchState) Brain.Screen.drawImageFromFile("iconOn.png", 10, 92);
    else Brain.Screen.drawImageFromFile("iconOff.png", 10, 92);
  }

  // void menuSlider(int menuSliderPct) {
  //   int sliderX(10);
  //   int sliderY(92); 
  //   Brain.Screen.setPenWidth(0);
  //   Brain.Screen.setPenColor(white);
  //   Brain.Screen.drawRectangle(sliderX + 50, sliderY + 15, (menuSliderPct * 3.5), 10, white);
  //   Brain.Screen.drawRectangle(sliderX + 50 + (menuSliderPct * 3.5), sliderY + 15, 350 - (menuSliderPct * 3.5), 10, pathColor);
  //   Brain.Screen.drawCircle(sliderX + 50 + (menuSliderPct * 3.5), sliderY + 20, 10, buttonColor);
  //   Brain.Screen.printAt(sliderX, sliderY + 11, false, "%d",  menuSliderPct); // Print settings
  //   if ((Brain.Screen.xPosition() - 60) / 3.5 >= 0 && (Brain.Screen.xPosition() - 60) / 3.5 <= 100)
  //   pages[currentPage].sliderPct = (Brain.Screen.xPosition() - 60) / 3.5;
  // }

  void menusSlider() {
    menuFolder();
    menuButton(1, currentPage);

    // uint8_t settings();

    // Brain.SDcard.savefile("settings", &settings, 1);

    // Brain.SDcard.appendfile("settings", &settings, 1);

    if (pages[currentPage].sliderPct < 0) pages[currentPage].sliderPct = 0;
    else if (pages[currentPage].sliderPct > 100) pages[currentPage].sliderPct = 100;

    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle( 110, 92, pages[currentPage].sliderPct * 2.6, 40, color(buttonColor));
    Brain.Screen.setPenWidth(2); // Set outline
    Brain.Screen.drawRectangle( 110, 92, 260, 40, color(transparent));

    Brain.Screen.setPenWidth(0); // Remove outline
    Brain.Screen.drawRectangle( 10, 92, 40, 40, color(buttonColor));
    Brain.Screen.drawRectangle( 60, 92, 40, 40, color(buttonColor));
    Brain.Screen.drawRectangle(380, 92, 40, 40, color(buttonColor));
    Brain.Screen.drawRectangle(430, 92, 40, 40, color(buttonColor));

    Brain.Screen.setFont(fontType::prop20);
    Brain.Screen.printAt(17, 120, false, "-10");
    Brain.Screen.printAt(74, 120, false, "-1");
    Brain.Screen.printAt(390, 120, false, "+1");
    Brain.Screen.printAt(433, 120, false, "+10");


    Brain.Screen.setFont(fontType::mono30);
    Brain.Screen.printAt(230, 120, false, "%d%%", pages[currentPage].sliderPct);

    Brain.Screen.drawRectangle(10, 142, 460, 90, color(buttonColor));
    Brain.Screen.setFont(fontType::prop20);
    Brain.Screen.printAt(20, 165, false, pages[currentPage].description);
    menuNavBar(currentPage, true);
  }

  void menuLcdDraw() {
    if      (pages[currentPage].pageType == auton)         menuAuton();
    else if (pages[currentPage].pageType == folder)        menuFolder();
    else if (pages[currentPage].pageType == sSwitch) menusSwitch();
    else if (pages[currentPage].pageType == sSlider) menusSlider();
  }

  void controllerDraw() {
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.clearLine();
    Controller.Screen.print(pages[currentPage].name);
  }

  void menuLcdTouch() {
    if (Brain.Screen.pressing() && !screenPressed) {
      screenPressed = true;

      if (Brain.Screen.xPosition() < 47 && Brain.Screen.yPosition() < 32) {
        currentPage = pages[currentPage].parentPageNumber; // Up
      } else if (Brain.Screen.xPosition() > 433 && Brain.Screen.yPosition() < 32) {
        currentPage = 0; // Home
      }
      if (pages[currentPage].pageType == folder) {
        if      (pages[currentPage].buttonOnePageNumber   != 0 && Brain.Screen.yPosition() >  42 && Brain.Screen.yPosition() <  82) currentPage = pages[currentPage].buttonOnePageNumber; // Button one
        else if (pages[currentPage].buttonTwoPageNumber   != 0 && Brain.Screen.yPosition() >  92 && Brain.Screen.yPosition() < 132) currentPage = pages[currentPage].buttonTwoPageNumber; // Button two
        else if (pages[currentPage].buttonThreePageNumber != 0 && Brain.Screen.yPosition() > 142 && Brain.Screen.yPosition() < 182) currentPage = pages[currentPage].buttonThreePageNumber; // Button three
        else if (pages[currentPage].buttonFourPageNumber  != 0 && Brain.Screen.yPosition() > 192 && Brain.Screen.yPosition() < 232) currentPage = pages[currentPage].buttonFourPageNumber; // Button four
      } else if (pages[currentPage].pageType == sSwitch) {
        if      (Brain.Screen.yPosition() > 87 && Brain.Screen.yPosition() < 137) pages[currentPage].switchState = !pages[currentPage].switchState;
      } else if (pages[currentPage].pageType == sSlider) {
        if      (Brain.Screen.yPosition() > 92 && Brain.Screen.yPosition() < 132) {
          if      (Brain.Screen.xPosition() >   10 && Brain.Screen.xPosition() < 50) pages[currentPage].sliderPct = pages[currentPage].sliderPct - 10;
          else if (Brain.Screen.xPosition() >   60 && Brain.Screen.xPosition() < 100) pages[currentPage].sliderPct = pages[currentPage].sliderPct -  1;
          else if (Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 420) pages[currentPage].sliderPct = pages[currentPage].sliderPct +  1;
          else if (Brain.Screen.xPosition() > 430 && Brain.Screen.xPosition() < 470) pages[currentPage].sliderPct = pages[currentPage].sliderPct + 10;
        }
      }
      menuLcdDraw();
      controllerDraw();
      Brain.Screen.render();
    } else if (!Brain.Screen.pressing() && screenPressed) {
      screenPressed = false;
    }
  }
//////

int main() {
  menuLcdDraw();
  Brain.Screen.render();
  while (1) {
    menuLcdTouch();
  }
}