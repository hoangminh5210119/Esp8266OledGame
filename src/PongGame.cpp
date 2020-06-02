#include "PongGame.h"

PongGame::PongGame(/* args */) {}

PongGame::~PongGame() {}

void PongGame::initLCD() {
  display.init();
  display.flipScreenVertically();
}

void PongGame::drawCourt() { display.drawRect(0, 0, 128, 64); }
void PongGame::drawScore() {
  if (ball_x >= 125) {
    display.drawString(30, 30, F("GAME END"));
    display.display();
    ball_x = 0;
    paddle_update = ball_update;
    score = 0;
    isGame = false;
    delay(3000);
    ball_update = millis();
  }
  display.drawString(60, 0, String(score));
}

void PongGame::setup() {
  initLCD();
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  display.clear();
  display.display();
  ball_update = millis();
  paddle_update = ball_update;
  a = new ButtonPullup(BUTTON_A);
  up = new ButtonPullup(BUTTON_UP);
  down = new ButtonPullup(BUTTON_DOWN);

  a->setOnClicked([this]() {
    if (isGame) {
      isExit = true;
    }
  });

  up->setOnClicked([this]() {
    isGame = true;
    player_y -= 5;
    if (player_y < 1) {
      player_y = 1;
    }
  });

  down->setOnClicked([this]() {
    isGame = true;
    player_y += 5;
    if (player_y + PADDLE_HEIGHT > 63) {
      player_y = 63 - PADDLE_HEIGHT;
    }
  });

  up->setOnHolding(
      [this]() {
        isGame = true;
        player_y -= 5;
        if (player_y < 1) {
          player_y = 1;
        }
      },
      100);
  down->setOnHolding(
      [this]() {
        isGame = true;
        player_y += 5;
        if (player_y + PADDLE_HEIGHT > 63) {
          player_y = 63 - PADDLE_HEIGHT;
        }
      },
      100);
}

void PongGame::updateKey() {
  a->update();
  up->update();
  down->update();
}

void PongGame::drawFlashScreen() {
  display.clear();
  display.drawString(45, 10, F("START"));
  display.drawString(15, 50, F("press any key to start"));
  display.display();
  ball_update = millis();
}

bool PongGame::update() {
  initLCD();
  while (true) {
    if (isGame) {
      unsigned long time = millis();
      if (isExit) {
        if (alert.alertOptions(str(D_EXIT_GAME), str(D_EXIT_GAME_MESSAGE),
                               str(D_AGREE_BUTTON), str(D_CANCEL_BUTTON))) {
          isExit = false;
          return true;
        }
        ball_update = millis();
        isExit = false;
        initLCD();
      }
      if (time > ball_update) {
        uint8_t new_x = ball_x + ball_dir_x;
        uint8_t new_y = ball_y + ball_dir_y;
        if (new_x == 0 || new_x == 127) {
          ball_dir_x = -ball_dir_x;
          new_x += ball_dir_x + ball_dir_x;
        }
        if (new_y == 0 || new_y == 63) {
          ball_dir_y = -ball_dir_y;
          new_y += ball_dir_y + ball_dir_y;
        }
        if (new_x == PLAYER_X && new_y >= player_y &&
            new_y <= player_y + PADDLE_HEIGHT) {
          ball_dir_x = -ball_dir_x;
          new_x += ball_dir_x + ball_dir_x;
          score = score + 1;
        }
        ball_x = new_x;
        ball_y = new_y;

        ball_update += BALL_RATE;
      }

      if (time > paddle_update) {
        paddle_update += PADDLE_RATE;
      }

      display.clear();
      drawCourt();
      display.fillCircle(ball_x, ball_y, 2);
      display.drawVerticalLine(PLAYER_X, player_y, PADDLE_HEIGHT);
      drawScore();
      display.display();
    } else {
      drawFlashScreen();
    }
    updateKey();
    delay(0);
  }
}