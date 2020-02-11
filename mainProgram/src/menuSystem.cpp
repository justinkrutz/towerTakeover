#include "vex.h"

using namespace vex;

/*===========================================================================*/


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

/*===========================================================================*/


bool screenPressed = false;
// bool edgeTrigger = Brain.Screen.pressing() && !screenPressed;
// int currentMenu = 0;
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

/*===========================================================================*/


Page pages[41] = {
  ////////    p, b1, b2, b3, b4, --type--, -color-, --------"name"--------, ----------"description"----------,  swSt,  sP
  /*  0 */  { 0,  1,  2,  3,  4,   folder,  __null,                    ""}, 
  /*  1 */  { 0,  5,  6,  0,  0,   folder,     red,                 "Red"}, 
  /*  2 */  { 0,  16,  17,  0,  0,   folder,    blue,                "Blue"}, 
  /*  3 */  { 0,  8,  0,  0,  0,   folder,  yellow,              "Skills"}, 
  /*  4 */  { 0,  9, 10, 11,  0,   folder,   green,               "Other"}, 
  /*  5 */  { 1,  0,  0,  0,  0,    auton,     red,          "Small goal",                  "Scores X cubes in small red goal"},
  /*  6 */  { 1,  0,  0,  0,  0,    auton,     red,          "Large goal",                  "Scores X cubes in large red goal"},
  /*  7 */  { 1,  0,  0,  0,  0,    auton,     red,                    "",                                                  ""},
  /*  8 */  { 3,  0,  0,  0,  0,    auton,  yellow,          "Skills one",                                "Does skills stuff."},
  /*  9 */  { 4, 12, 13, 14, 15,   folder,   green,            "Settings"},                   
  /* 10 */  { 4,  0,  0,  0,  0,    auton,   green,                "None",                                     "Does nothing."},
  /* 11 */  { 4,  0,  0,  0,  0,    auton,   green,       "Drive Forward",              "Drives forwards and scores one cube."},
  /* 12 */  { 9,  0,  0,  0,  0,  sSlider,   green,      "Useless slider",                                       "Is useless.", false,  57},
  /* 13 */  { 9,  0,  0,  0,  0,  sSwitch,   green,       "Self destruct",                    "Toggles self dectruct feature.",  true},
  /* 14 */  { 9,  0,  0,  0,  0,  sSwitch,   green,                 "Win",                            "Toggles match outcome.", false},  
  /* 15 */  { 9,  0,  0,  0,  0,  sSwitch,   green,              "Flight",                           "Toggles ability to fly.", false},  
  /* 16 */  { 2,  0,  0,  0,  0,    auton,    blue,          "Small goal",                  "Scores 8 cubes in small blue goal"},
  /* 17 */  { 2,  0,  0,  0,  0,    auton,    blue,          "Large goal",                  "Scores X cubes in large blue goal"},
  /* 18 */  
  /* 19 */  
  /* 20 */  
  /* 21 */    
  /* 22 */  
  /* 23 */  
  /* 24 */    
  /* 25 */  
  /* 26 */  
  /* 27 */  
  /* 28 */    
  /* 29 */  
  /* 30 */  
  /* 31 */    
  /* 32 */  
  /* 33 */  
  /* 34 */  
  /* 35 */  
  /* 36 */  
  /* 37 */  
  /* 38 */  
  /* 39 */  
  /* 40 */  
  ////////    p, b1, b2, b3, b4, --type--, -color-, --------"name"--------, ----------"description"----------,  swSt,  sP
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
  Brain.Screen.drawRectangle(0, 0, 480, 240, color(backgroundColor)); // Draw background
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
}

void menusSwitch() {
  Brain.Screen.setPenWidth(0); // Remove outline
  Brain.Screen.drawRectangle(10, 142, 460, 90, color(buttonColor));
  menuButton(1, currentPage);
  Brain.Screen.setFont(fontType::prop20);
  Brain.Screen.printAt(20, 165, false, pages[currentPage].description);
  if (pages[currentPage].switchState) Brain.Screen.drawImageFromFile("iconOn.png", 10, 92);
  else Brain.Screen.drawImageFromFile("iconOff.png", 10, 92);
}

void menusSlider() {
  menuButton(1, currentPage);

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
}

void menuLcdDraw() {
  menuNavBar(currentPage, (pages[currentPage].pageType != folder));
  if      (pages[currentPage].pageType == auton)         menuAuton();
  else if (pages[currentPage].pageType == folder)        menuFolder();
  else if (pages[currentPage].pageType == sSwitch) menusSwitch();
  else if (pages[currentPage].pageType == sSlider) menusSlider();
  Brain.Screen.render();

}

int selectedAuton() {
  if (pages[currentPage].pageType == auton) {
    return currentPage;
  } else {
    return 10;
  }


  // Brain.SDcard.loadfile("lastAuton", selectedAuton, 2);
  // switch(currentPage){ 
  //   case  5: return  5;
  //   case  6: return  6;
  //   case  7: return  7;
  //   case  8: return  8;
  //   case 11: return 11;
  //   default: return 10;
  // Brain.SDcard.("lastAuton", selectedAuton, 2);
  // }
}

void controllerDraw() {
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.clearLine(3);
  // Controller.Screen.print("");
  Controller1.Screen.print(pages[selectedAuton()].name);
  // Controller.Screen.print(pages[currentPage].name);
}

void menuLcdTouch(){
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
    }
    else if (pages[currentPage].pageType == sSwitch) {
      if      (Brain.Screen.yPosition() > 87 && Brain.Screen.yPosition() < 137) pages[currentPage].switchState = !pages[currentPage].switchState;
    }
    else if (pages[currentPage].pageType == sSlider) {
      if      (Brain.Screen.yPosition() > 92 && Brain.Screen.yPosition() < 132) {
        if      (Brain.Screen.xPosition() >   10 && Brain.Screen.xPosition() < 50) pages[currentPage].sliderPct = pages[currentPage].sliderPct - 10;
        else if (Brain.Screen.xPosition() >   60 && Brain.Screen.xPosition() < 100) pages[currentPage].sliderPct = pages[currentPage].sliderPct -  1;
        else if (Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 420) pages[currentPage].sliderPct = pages[currentPage].sliderPct +  1;
        else if (Brain.Screen.xPosition() > 430 && Brain.Screen.xPosition() < 470) pages[currentPage].sliderPct = pages[currentPage].sliderPct + 10;
      }
    }
    menuLcdDraw();
    controllerDraw();
  } else if (!Brain.Screen.pressing() && screenPressed) {
    screenPressed = false;
  }
}

void autonIndicator() {
  Brain.Screen.clearScreen(pages[selectedAuton()].pageColor);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(fontType::prop60);
  Brain.Screen.printAt(75, 125, false, pages[selectedAuton()].name);
  Brain.Screen.render();
}