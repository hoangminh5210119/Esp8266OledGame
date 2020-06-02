#ifndef OledMenu_h
#define OledMenu_h
#include "A_config.h"
#include "Arduino.h"
#include "SimpleList.h"
#include <SimpleButton.h>

using namespace simplebutton;

#define DISPLAY_GUI true
#define DISPLAY_LIST false

struct MenuNode {
  const uint8_t *image;
  std::function<String()>
      getStr;                  // function used to create the displayed string
  std::function<void()> click; // function that is executed when node is clicked
  std::function<void()>
      hold; // function that is executed when node is pressed for > 800ms
};

struct Menu {
  SimpleList<MenuNode> *list;
  Menu *parentMenu;
  uint8_t selected;
  bool isGUI;
  std::function<void()>
      build; // function that is executed when button is clicked
};

class OledMenu {
private:
  Button *up = NULL;
  Button *down = NULL;
  Button *a = NULL;
#ifdef ESP32
  Button *left = NULL;
  Button *right = NULL;
#endif

  DEAUTHER_DISPLAY;

  uint32_t currentTime = millis();

  int16_t selectedID = 0;    // i.e. access point ID to draw the apMenu
  uint8_t scrollCounter = 0; // for horizontal scrolling

  uint32_t scrollTime = 0; // last time a character was moved
  uint32_t drawTime = 0;   // last time a frame was drawn
  uint32_t startTime = 0;  // when the screen was enabled
  uint32_t buttonTime = 0; // last time a button was pressed

  const uint8_t maxLen = 20;
  const uint8_t lineHeight = 12;
  const uint8_t buttonDelay = 250;
  const uint8_t drawInterval = 100; // 100ms = 10 FPS
  const uint16_t scrollSpeed = 500; // time interval in ms
  const uint16_t screenIntroTime = 0;
  const uint16_t screenWidth = 128;
  const uint16_t sreenHeight = 64;

  const uint16_t centerX = 128 / 2;
  const uint16_t centerY = 64 / 2;

  
  void drawString(int x, int y, String str);
  void drawString(int row, String str);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawImage(int16_t xMove, int16_t yMove, int16_t width, int16_t height,
                 const uint8_t *xbm);
  void drawImageCenter(int16_t width, int16_t height, const uint8_t *xbm);
  void drawImageCenterHorizontal(int16_t x, int16_t width, int16_t height,
                                 const uint8_t *xbm);
  void drawImageCenterVertical(int16_t y, int16_t width, int16_t height,
                               const uint8_t *xbm);

  void drawMenu();
  void drawList();
  void drawGUI();
  void clearMenu(Menu *menu);

  Menu *currentMenu;

public:
  OledMenu(/* args */);
  ~OledMenu();
  void setup();
  void update();

  void reconnectOledI2C();
  void configLCD();

  void changeMenu(Menu *menu);
  void goBack();

  void createMenu(Menu *menu, Menu *parent, bool isGUI,
                  std::function<void()> build);
  // void drawMenu(Menu *currentMenu);

  // FOR GUI DISPLAY
  void addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                   std::function<void()> click, std::function<void()> hold);
  void addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                   std::function<void()> click);
  void addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                   Menu *next);
  // void addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
  // std::function<void()> click);

  // FOR TEXT DISPLAY
  void addMenuNode(Menu *menu, std::function<String()> getStr,
                   std::function<void()> click, std::function<void()> hold);
  void addMenuNode(Menu *menu, std::function<String()> getStr,
                   std::function<void()> click);
  void addMenuNode(Menu *menu, std::function<String()> getStr, Menu *next);
  void addMenuNode(Menu *menu, const char *ptr, std::function<void()> click);
  void addMenuNode(Menu *menu, const char *ptr, Menu *next);
};

#endif