#ifndef PongGame_h
#define PongGame_h

#include "A_config.h"
#include "Arduino.h"
#include "SSD1306Wire.h"
#include <SimpleButton.h>
#include "Alert.h"
#include "language.h"

using namespace simplebutton;

extern Alert alert;

class PongGame {
private:
  DEAUTHER_DISPLAY;

  const unsigned long PADDLE_RATE = 33;
  const unsigned long BALL_RATE = 16;
  const uint8_t PADDLE_HEIGHT = 24;

  uint8_t ball_x = 64, ball_y = 32;
  uint8_t ball_dir_x = 1, ball_dir_y = 1;
  unsigned long ball_update;

  unsigned long paddle_update;
  const uint8_t CPU_X = 12;
  uint8_t cpu_y = 16;

  const uint8_t PLAYER_X = 115;
  int player_y = 16;

  unsigned int score = 0;

  Button *a = NULL;
  Button *up = NULL;
  Button *down = NULL;

  bool isExit = false;
  bool isGame = false;

  /* data */
  void initLCD();
  void drawCourt();
  void drawScore();
  void updateKey();

  void drawFlashScreen();

public:
  PongGame(/* args */);
  ~PongGame();
  void setup();
  bool update();
};

#endif