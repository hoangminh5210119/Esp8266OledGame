#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include "A_config.h"
#include "Arduino.h"
#include "SSD1306Wire.h"
#include "Alert.h"
#include "language.h"
#include <SimpleButton.h>

using namespace simplebutton;

// #include "images.h"
// #define DEMO_DURATION 3000
// typedef void (*Demo)(void);
enum FLAPPY_BIRD_KEY_ACTION { BIRD_PRESS, BIRD_NOT_PRESS, BIRD_EXIT, BIRD_GAME_OVER };

enum data { num1, num2 };
extern Alert alert;

class FlappyBirdGame {
private:
  DEAUTHER_DISPLAY;
  float zidx[4];
  int prazan[4];
  int razmak = 32;
  int sirinaProlaza = 30;

  int score = 0;
  int stis = 0;
  float fx = 30.00;
  float fy = 22.00;
  int smjer = 0;
  unsigned long trenutno = 0;

  int igra = 0;
  int frame = 0;
  int sviraj = 0;
  unsigned long ton = 0;

  Button *up = NULL;
  Button *down = NULL;
  Button *a = NULL;
  Button *b = NULL;

  int key = FLAPPY_BIRD_KEY_ACTION::BIRD_NOT_PRESS;

  void run(int key);
  void updateKey();
  void initLCD();

public:
  FlappyBirdGame(/* args */);
  ~FlappyBirdGame();
  void setup();
  bool update();
};

#endif