#ifndef GAME_H
#define GAME_H

#include "A_config.h"
#include "Arduino.h"
#include "SSD1306Wire.h"
#include <SimpleButton.h>
#include "Alert.h"
#include "language.h"

using namespace simplebutton;

extern Alert alert;

enum KEY_ACTION { LEFT_UP, LEFT_DOWN, EXIT, UNPRESS, GAME_OVER };

class TRexGame {
private:
  DEAUTHER_DISPLAY;
  int keyLast = -1;
  int dino_x = 0, dino_y = 35;
  int dino_type = 0, dino_dir = -1, dino_count = 0;
  int cactus_x = 95, cactus_y = 34;
  int cactus_type = 0;
  int ground_x = 0, ground_y = 50;
  int score = 0, hiscore = 0;
  int game_over = 0;
  long game_timeLast = 0;
  long display_timeLast = 0;

  char collisionBuff1[24] = {31, 30, 29, 28, 27, 23, 23, 23, 20, 20, 20, 20,
                             20, 20, 20, 20, 25, 25, 25, 30, 32, 34, 35, 35};
  char collisionBuff2[31] = {27, 26, 25, 24, 22, 19, 18, 18, 18, 14, 13,
                             13, 13, 13, 13, 13, 13, 13, 14, 20, 19, 19,
                             20, 26, 27, 28, 29, 33, 34, 34, 35};
  char collisionBuff3[31] = {32, 31, 30, 29, 24, 23, 22, 21, 20, 16, 16,
                             17, 13, 13, 13, 13, 13, 13, 13, 13, 19, 20,
                             20, 23, 27, 27, 28, 28, 34, 35, 35};

  void gameInit(void);
  boolean gameCollision(void);
  void gameDraw(void);

  Button *up = NULL;
  Button *down = NULL;
  Button *a = NULL;
  Button *b = NULL;

  int key = KEY_ACTION::UNPRESS;

  void updateKey();
  int keyPressed(void);
  void initLCD();

public:
  TRexGame();
  ~TRexGame();
  void setup();
  bool update();
};

#endif