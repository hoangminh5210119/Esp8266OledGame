#include "FlappyBirdGame.h"
#include "images.h"

FlappyBirdGame::FlappyBirdGame(/* args */) {}

FlappyBirdGame::~FlappyBirdGame() {}

void FlappyBirdGame::setup() {
  initLCD();
  up = new ButtonPullup(BUTTON_UP);
  down = new ButtonPullup(BUTTON_DOWN);
  a = new ButtonPullup(BUTTON_A);

  up->setOnClicked([this]() {
    key = FLAPPY_BIRD_KEY_ACTION::BIRD_PRESS;
    if (igra == 0) {
      igra = 1;
    }
  });
  down->setOnClicked([this]() {
    key = FLAPPY_BIRD_KEY_ACTION::BIRD_PRESS;
    if (igra == 0) {
      igra = 1;
    }
  });
  a->setOnClicked([this]() {
    if (igra == 1) {
      key = FLAPPY_BIRD_KEY_ACTION::BIRD_EXIT;
    }
    igra = 1;
  });
}

void FlappyBirdGame::initLCD() {
  display.init();
#ifndef FLIP_DIPLAY
  display.flipScreenVertically();
#endif // ifndef FLIP_DIPLAY
  display.clear();
  display.display();
}

void FlappyBirdGame::run(int key) {
  display.clear();

  if (igra == 0) {
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 4, F("Flappy "));
    display.drawXbm(0, 0, 128, 64, pozadina);
    display.drawXbm(20, 32, 14, 9, ptica);

    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 44, F("press to start"));
  }

  if (igra == 1) {
    display.setFont(ArialMT_Plain_10);
    display.drawString(3, 0, String(score));

    if (digitalRead(BUTTON_UP) == 0 || digitalRead(BUTTON_DOWN) == 0) {
      if (stis == 0) {
        trenutno = millis();
        smjer = 1;
        sviraj = 1;
        stis = 1;
        ton = millis();
      }
    } else {
      stis = 0;
    }

    for (int j = 0; j < 4; j++) {
      display.setColor(WHITE);
      display.fillRect(zidx[j], 0, 6, 64);
      display.setColor(BLACK);
      display.fillRect(zidx[j], prazan[j], 6, sirinaProlaza);
    }

    display.setColor(WHITE);

    display.drawXbm(fx, fy, 14, 9, ptica);

    for (int j = 0; j < 4; j++) {
      zidx[j] = zidx[j] - 0.01;
      if (zidx[j] < -7) {
        score = score + 1;
        prnt("score: ");
        prntln(String(score));
        prazan[j] = random(8, 32);

        zidx[j] = 128;
      }
    }
    if ((trenutno + 185) < millis())
      smjer = 0;

    if ((ton + 40) < millis())
      sviraj = 0;

    if (smjer == 0)
      fy = fy + 0.01;
    else
      fy = fy - 0.03;
    if (fy > 63 || fy < 0) {
      igra = 0;
      fy = 22;
      score = 0;
      for (int i = 0; i < 4; i++) {
        zidx[i] = 128 + ((i + 1) * razmak);
        { prazan[i] = random(4, 30); }
      }
    }

    for (int m = 0; m < 4; m++)
      if (zidx[m] <= fx + 7 && fx + 7 <= zidx[m] + 6) {

        if (fy < prazan[m] || fy + 8 > prazan[m] + sirinaProlaza) {
          igra = 0;
          fy = 22;
          score = 0;
          for (int i = 0; i < 4; i++) {
            zidx[i] = 128 + ((i + 1) * razmak);
            { prazan[i] = random(8, 32); }
          }
        }
      }
    display.drawRect(0, 0, 128, 64);
  }

  display.display();
}

void FlappyBirdGame::updateKey() {
  up->update();
  down->update();
  a->update();
}

bool FlappyBirdGame::update() {
  initLCD();
  while (1) {
    updateKey();
    if (key == BIRD_PRESS) {
      run(data::num1);
    } else {
      run(data::num2);
    }

    if (key == BIRD_EXIT) {
      if (alert.alertOptions(str(D_EXIT_GAME), str(D_EXIT_GAME_MESSAGE),
                             str(D_AGREE_BUTTON), str(D_CANCEL_BUTTON))) {
        key = BIRD_NOT_PRESS;
        return true;
      }
      key = BIRD_NOT_PRESS;
      initLCD();
    }
  }
}