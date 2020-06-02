#include "Alert.h"
#include "Arduino.h"
#include "CarRaceGame.h"
#include "FlappyBirdGame.h"
#include "OledMenu.h"
#include "PongGame.h"
#include "TRexGame.h"
#include "images.h"

Alert alert;

CarRaceGame carRaceGame;
FlappyBirdGame flappyBirdGame;
PongGame pongGame;
TRexGame tRexGame;

OledMenu menu;
Menu mainMenu;
Menu gameMenu;

void setup() {
  Serial.begin(115200);
  menu.setup();
  alert.setupButton();
  //   alert

  menu.createMenu(&mainMenu, NULL, DISPLAY_GUI, []() {
    menu.addMenuNode(&mainMenu, menu_game_bits, "GAME", &gameMenu);
  });

  menu.createMenu(&gameMenu, &mainMenu, DISPLAY_GUI, []() {
    menu.addMenuNode(&gameMenu, raceCarGame_bits, "Car", []() {
      carRaceGame.setup();
      carRaceGame.update();
      menu.changeMenu(&gameMenu);
      menu.reconnectOledI2C();
      menu.configLCD();
    });

    menu.addMenuNode(&gameMenu, flappy_bird_bits, "Flappy Bird", []() {
      flappyBirdGame.setup();
      flappyBirdGame.update();
      menu.changeMenu(&gameMenu);
      menu.reconnectOledI2C();
      menu.configLCD();
    });
    menu.addMenuNode(&gameMenu, PongGame_bits, "pong ", []() {
      pongGame.setup();
      pongGame.update();
      menu.changeMenu(&gameMenu);
      menu.reconnectOledI2C();
      menu.configLCD();
    });
    menu.addMenuNode(&gameMenu, dinosauria_bits, "T-Rex", []() {
      tRexGame.setup();
      tRexGame.update();
      menu.changeMenu(&gameMenu);
      menu.reconnectOledI2C();
      menu.configLCD();
    });
  });
  menu.changeMenu(&mainMenu);
}

void loop() { menu.update(); }