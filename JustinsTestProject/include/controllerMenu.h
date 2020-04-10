#define folder 0
#define auton 1
#define sSwitch 2
#define sSlider 3

class controllerMenu {
  public: 
    void printMenu( void );

    void scrollLeft( void );
    void scrollRight( void );
    void select( void );
    void back( void );

  private:
    int cursorLocation;

    void printFolder( void );
    void printAuton( void );
    void printSettingSlider( void );
    void printSettingSwitch( void );
};

extern controllerMenu ControllerMenu;