#include "TRexGame.h"
#include "images.h"

TRexGame::TRexGame() {}
TRexGame::~TRexGame() {}

void TRexGame::gameInit(void) {
  dino_x = 0;
  dino_y = 35;
  dino_type = 0;
  dino_dir = -1;
  dino_count = 0;

  cactus_x = 95;
  cactus_y = 34;
  cactus_type = 0;

  ground_x = 0;
  ground_y = 50;

  if (score > hiscore)
    hiscore = score;
  score = 0;

  game_over = 0;
}

boolean TRexGame::gameCollision(void) {
  if (dino_type == 0 || dino_type == 1) {
    if (cactus_type == 0 && cactus_x > -8 && cactus_x < 17) {
      if (dino_y >= collisionBuff1[cactus_x + 7])
        return true;
    } else if (cactus_type == 1 && cactus_x > -12 && cactus_x < 20) {
      if (dino_y >= collisionBuff2[cactus_x + 11])
        return true;
    } else if (cactus_type == 2 && cactus_x > -12 && cactus_x < 20) {
      if (dino_y >= collisionBuff3[cactus_x + 11])
        return true;
    } else if (cactus_type == 3 || cactus_type == 4) {
      if (cactus_x < 12)
        return true;
    }
  } else if (dino_type == 2 || dino_type == 3) {
    if ((cactus_type == 0 || cactus_type == 1 || cactus_type == 2) &&
        cactus_x < 27)
      return true;
  }

  return false;
}

void TRexGame::gameDraw(void) {
  char str[32];

  display.clear();
  display.drawXbm(ground_x, ground_y, 96, 16, ground1);
  display.drawXbm(ground_x - 95, ground_y, 96, 16, ground1);

  if (cactus_type == 0)
    display.drawXbm(cactus_x, cactus_y + 7, 8, 16, cactus1);
  else if (cactus_type == 1)
    display.drawXbm(cactus_x, cactus_y, 16, 24, cactus2);
  else if (cactus_type == 2)
    display.drawXbm(cactus_x, cactus_y, 16, 24, cactus3);
  else if (cactus_type == 3)
    display.drawXbm(cactus_x, cactus_y - 9, 24, 24, bird1);
  else if (cactus_type == 4)
    display.drawXbm(cactus_x, cactus_y - 9, 24, 24, bird2);

  display.drawString(67, 0, String(score));
  display.drawString(12, 0, "HI " + String(hiscore));

  if (dino_type == 0)
    display.drawXbm(dino_x, dino_y, 24, 24, dino2);
  else if (dino_type == 1)
    display.drawXbm(dino_x, dino_y, 24, 24, dino3);
  else if (dino_type == 2)
    display.drawXbm(dino_x, dino_y + 9, 32, 16, dino4);
  else if (dino_type == 3)
    display.drawXbm(dino_x, dino_y + 9, 32, 16, dino5);
  else if (dino_type == 4)
    display.drawXbm(dino_x, dino_y, 24, 24, dino6);

  if (game_over) {
    key = GAME_OVER;
    display.drawString(30, 12, F("GAME OVER"));
    display.drawXbm(50, 24, 25, 20, GOver);
    display.display();

    while (key == GAME_OVER) {
      up->update();
      down->update();
      a->update();
      delay(0);
    }
  }

  display.display();
}

void TRexGame::initLCD() {
  display.init();
#ifndef FLIP_DIPLAY
  display.flipScreenVertically();
#endif // ifndef FLIP_DIPLAY
  display.clear();
  display.display();
}

void TRexGame::setup() {
  initLCD();
  up = new ButtonPullup(BUTTON_UP);
  down = new ButtonPullup(BUTTON_DOWN);
  a = new ButtonPullup(BUTTON_A);

  up->setOnClicked([this]() { key = KEY_ACTION::LEFT_UP; });
  down->setOnClicked([this]() { key = KEY_ACTION::LEFT_DOWN; });
  a->setOnClicked([this]() { key = KEY_ACTION::EXIT; });

  display.clear();
  display.drawXbm(ground_x, ground_y, 96, 16, ground1);
  display.drawXbm(96, ground_y, 96, 16, ground2);
  display.drawXbm(dino_x, dino_y, 24, 24, dino1);
  display.drawString(30, 12, F("GAME T-REX"));
  display.display();
  key = GAME_OVER;
  while (key == GAME_OVER) {
    updateKey();
    delay(0);
  }
  gameInit();
}

void TRexGame::updateKey() {
  up->update();
  down->update();
  a->update();
}

int TRexGame::keyPressed(void) {

  if (!digitalRead(BUTTON_UP)) {
    return LEFT_UP;
  } else if (!digitalRead(BUTTON_DOWN)) {
    return LEFT_DOWN;
  } else {
    return UNPRESS;
  }
}

bool TRexGame::update() {
  initLCD();
  while (1) {
    updateKey();
    if (key == KEY_ACTION::EXIT) {
      if (alert.alertOptions(str(D_EXIT_GAME), str(D_EXIT_GAME_MESSAGE),
                             str(D_AGREE_BUTTON), str(D_CANCEL_BUTTON))) {
        key = KEY_ACTION::UNPRESS;
        return true;
      }
      key = KEY_ACTION::UNPRESS;
      initLCD();
    }

    if (millis() - game_timeLast > 10) {
      game_timeLast = millis();

      key = keyPressed();
      if (key == LEFT_UP || dino_y != 35) {
        dino_y += dino_dir;
        if (dino_y == 35 || dino_y == 5)
          dino_dir *= -1;
      } else if (key == LEFT_DOWN && keyLast == UNPRESS && dino_y == 35) {
        dino_type = 2;
      } else if (key == UNPRESS && keyLast == LEFT_DOWN) {
        dino_type = 0;
      }

      keyLast = key;

      cactus_x--;
      if (cactus_x <= -12) {
        cactus_x = 95;
        cactus_type = random(4);
      }

      ground_x--;
      if (ground_x < 0)
        ground_x = 95;
    }

    if (millis() - display_timeLast > 50) {
      display_timeLast = millis();

      score++;
      dino_count++;

      if (gameCollision()) {
        game_over = 1;
        dino_type = 4;
      } else {
        if (dino_count >= 4) {
          dino_count = 0;

          if (dino_type == 0)
            dino_type = 1;
          else if (dino_type == 1)
            dino_type = 0;
          else if (dino_type == 2)
            dino_type = 3;
          else if (dino_type == 3)
            dino_type = 2;

          if (cactus_type == 3)
            cactus_type = 4;
          else if (cactus_type == 4)
            cactus_type = 3;
        }
      }
      gameDraw();
      if (game_over) {
        gameInit();
      }
    }
    delay(0);
  }
}