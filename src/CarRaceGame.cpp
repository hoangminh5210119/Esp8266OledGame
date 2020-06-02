#include "CarRaceGame.h"
#include "images.h"

CarRaceGame::CarRaceGame(/* args */) {}

CarRaceGame::~CarRaceGame() {}

void CarRaceGame::setup() {

  initLCD();
  a = new ButtonPullup(BUTTON_A);
  up = new ButtonPullup(BUTTON_UP);
  down = new ButtonPullup(BUTTON_DOWN);

  a->setOnClicked([this]() { isExit = true; });

  down->setOnClicked([this]() { dirPressed = DIRLEFT; });

  up->setOnClicked([this]() { dirPressed = DIRRIGHT; });
  // a->setOnHolding([this]() { isExit = true; }, 1000);

  enemy0PosX = 200;
  enemy0PosY = randomPosY();
  enemy1PosX = 250;
  enemy1PosY = randomPosY();
  enemy2PosX = 300;
  enemy2PosY = randomPosY();
}

bool CarRaceGame::update() {
  initLCD();
  splashScreen();
  waitForPress();
  isExit = false;
  while (true) {
    if (isExit) {
      if (alert.alertOptions(str(D_EXIT_GAME), str(D_EXIT_GAME_MESSAGE), str(D_AGREE_BUTTON), str(D_CANCEL_BUTTON))) {
        isExit = false;
        break;
      }
      isExit = false;
      initLCD();
    }
    updateKey();
    updateGame();
  }
  return true;
}

void CarRaceGame::updateKey() {
  a->update();
  up->update();
  down->update();
}

void CarRaceGame::initLCD() {
  display.init();
  display.clear();
  display.flipScreenVertically();
}

void CarRaceGame::moveCar() {
  switch (dirPressed) {
  case DIRRIGHT:
    if (carPosYCnt == 0) {
      carPosYCnt = 0;
    } else {
      carPosYCnt = carPosYCnt - 1;
    }
    break;

  case DIRLEFT:
    carPosYCnt = carPosYCnt + 1;
    if (carPosYCnt > 3) {
      carPosYCnt = 3;
    }
    break;
  }
  dirPressed = 0;
}
uint8_t CarRaceGame::randomPosX() {
  uint8_t posValTmp = 0;
  posValTmp = random(129, 230);
  return (posValTmp);
}
uint8_t CarRaceGame::randomPosY() {
  uint8_t laneVal = 0;
  laneVal = random(0, 4);
  return (lanePosArr[laneVal]);
}
void CarRaceGame::setGameSpeed() {
  if (drawSpeed < 21) {
    drawSpeed = drawSpeed + 2;
  }
}
void CarRaceGame::detectCrash() {
  if (enemy0PosX <= 28 && enemy0PosX >= 0 &&
      enemy0PosY == carPosY[carPosYCnt]) {
    gameOver(); // line 0
  }
  if (enemy1PosX <= 28 && enemy1PosX >= 0 &&
      enemy1PosY == carPosY[carPosYCnt]) {
    gameOver(); // line 1
  }
  if (enemy2PosX <= 28 && enemy2PosX >= 0 &&
      enemy2PosY == carPosY[carPosYCnt]) {
    gameOver(); // line 2
  }
}
void CarRaceGame::updateSpeed() {
  if (millis() - _oldTimeUpdateSpeed < timeUpdateSpeed) {
    return;
  }
  _oldTimeUpdateSpeed = millis();

  if (cntSpeed > 100) {
    cntSpeed = 0;
    setGameSpeed();
  }
  cntSpeed = cntSpeed + 1;

  score = score + 1;

  roadLineX1 = roadLineX1 - drawSpeed;
  roadLineX2 = roadLineX2 - drawSpeed;
  roadLineX3 = roadLineX3 - drawSpeed;
  roadLineX4 = roadLineX4 - drawSpeed;
  roadLineX5 = roadLineX5 - drawSpeed;

  if (roadLineX1 < -35) {
    roadLineX1 = 128;
  }
  if (roadLineX2 < -35) {
    roadLineX2 = 128;
  }
  if (roadLineX3 < -35) {
    roadLineX3 = 128;
  }
  if (roadLineX4 < -35) {
    roadLineX4 = 128;
  }
  if (roadLineX5 < -35) {
    roadLineX5 = 128;
  }

  enemy0PosX = enemy0PosX - drawSpeed;
  enemy1PosX = enemy1PosX - drawSpeed;
  enemy2PosX = enemy2PosX - drawSpeed;

  if (enemy0PosX < -30) {
    enemy0PosX = 200;
    enemy0PosY = randomPosY();
  }
  if (enemy1PosX < -30) {
    enemy1PosX = 250;
    enemy1PosY = randomPosY();
    // checkCarPostion();
  }
  if (enemy2PosX < -30) {
    enemy2PosX = 300;
    enemy2PosY = randomPosY();
    // checkCarPostion();
  }
}
void CarRaceGame::drawRoad() {
  display.fillRect(roadLineX1, 15, 30, 2);
  display.fillRect(roadLineX1, 30, 30, 2);
  display.fillRect(roadLineX1, 45, 30, 2);
  display.fillRect(roadLineX2, 15, 30, 2);
  display.fillRect(roadLineX2, 30, 30, 2);
  display.fillRect(roadLineX2, 45, 30, 2);
  display.fillRect(roadLineX3, 15, 30, 2);
  display.fillRect(roadLineX3, 30, 30, 2);
  display.fillRect(roadLineX3, 45, 30, 2);
  display.fillRect(roadLineX4, 15, 30, 2);
  display.fillRect(roadLineX4, 30, 30, 2);
  display.fillRect(roadLineX4, 45, 30, 2);
  display.fillRect(roadLineX5, 15, 30, 2);
  display.fillRect(roadLineX5, 30, 30, 2);
  display.fillRect(roadLineX5, 45, 30, 2);
}
void CarRaceGame::enemysDraw() {
  display.drawXbm(enemy0PosX, enemy0PosY, ENEMY0_WIDTH, ENEMY0_HEIGHT, ENEMY0);
  display.drawXbm(enemy1PosX, enemy1PosY, ENEMY1_WIDTH, ENEMY1_HEIGHT, ENEMY1);
  display.drawXbm(enemy2PosX, enemy2PosY, ENEMY2_WIDTH, ENEMY2_HEIGHT, ENEMY2);
}
void CarRaceGame::updateDisplay() {
  display.drawXbm(carPosX, carPosY[carPosYCnt], 30, 15, CARSPRITE);
  display.drawString(100, 0, String(score));
  display.display();
}
void CarRaceGame::waitForPress() {
  display.clear();
  while (true) {
    display.drawString(23, 24, F("Reckless"));
    display.drawString(36, 34, F("Racer"));
    display.drawXbm(74, 24, CARWIDTH, CARHEIGHT, CARSPRITE);
    display.drawString(25, 43, F("press any key"));
    display.drawString(10, 0, "High Score: " + String(highScore));
    display.display();
    dirPressed = 0;
    if (!digitalRead(BUTTON_A) || !digitalRead(BUTTON_UP) ||
        !digitalRead(BUTTON_DOWN)) {
      break;
    }
    delay(0);
  }
}
void CarRaceGame::updateGame() {
  display.clear();
  moveCar();
  drawRoad();
  enemysDraw();
  updateSpeed();
  detectCrash();
  updateDisplay();
}
void CarRaceGame::gameOver() {
  display.drawXbm(carPosX, carPosY[carPosYCnt], 30, 15, CARSPRITE);
  display.drawString(10, 23, F("GAME OVER"));
  display.display();
  restartGame();
  waitForPress();
}
void CarRaceGame::restartGame() {
  if (score >= highScore) // check to see if score higher than high score
  {
    highScore = score; // single if statment to update high score
  }

  score = 0;
  drawSpeed = 4;
  carPosYCnt = 0;
  enemy0PosX = 200;
  enemy0PosY = randomPosY();
  enemy1PosX = 250;
  enemy1PosY = randomPosY();
  enemy2PosX = 300;
  enemy2PosY = randomPosY();
}

void CarRaceGame::splashScreen() {
  display.clear();
  display.drawXbm(0, 0, CRASHWIDTH, CRASHHEIGHT, CRASH);
  display.display();
  delay(2000);
}
