#ifndef CarRaceGame_h
#define CarRaceGame_h

#include "A_config.h"
#include "Alert.h"
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "SSD1306Wire.h"
#include "language.h"
#include <SimpleButton.h>
#include <Wire.h> // Only needed for Arduino 1.6.5 and earlier

using namespace simplebutton;

extern Alert alert;

#define DIRLEFT 3
#define DIRRIGHT 4

class CarRaceGame {
private:
  uint8_t dirPressed = 0;
  // vars for the position of the car
  uint8_t carPosX = 1;
  uint8_t carPosY[4] = {0, 16, 32, 48}; // needs value cahnging the the array

  uint8_t lanePosArr[4] = {0, 16, 32, 48}; // array to store where each lane is
  uint8_t carPosYCnt = 0;
  uint8_t carYTmp = 0;
  int roadLineX1 = 51;
  int roadLineX2 = 102;
  int roadLineX3 = 153;
  int roadLineX4 = 254;
  int roadLineX5 = 200;

  int lineRoadWidth = 30;
  uint8_t drawSpeed = 4;

  int enemy0PosX = 255;
  int enemy0PosY = 0;
  int enemy1PosX = 255;
  int enemy1PosY = 0;
  int enemy2PosX = 255;
  int enemy2PosY = 0;

  long score = 0;
  long compare = 0;
  long highScore = 0;

  unsigned long _oldTimeUpdateSpeed = millis();
  int timeUpdateSpeed = 200;
  int cntSpeed = 0;

  bool isExit = false;

  DEAUTHER_DISPLAY;

  Button *up = NULL;
  Button *down = NULL;
  Button *a = NULL;
  Button *b = NULL;

  void updateKey();
  void initLCD();

  void moveCar();
  uint8_t randomPosX();
  uint8_t randomPosY();
  void setGameSpeed();
  void detectCrash();
  void updateSpeed();
  void drawRoad();
  void enemysDraw();
  void updateDisplay();
  void waitForPress();
  void updateGame();
  void gameOver();
  void restartGame();
  void checkCarPostion();
  void splashScreen();

public:
  CarRaceGame(/* args */);
  ~CarRaceGame();

  void setup();
  bool update();
};
#endif