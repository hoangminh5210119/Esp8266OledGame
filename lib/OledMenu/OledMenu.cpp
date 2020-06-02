#include "OledMenu.h"
#include "Language.h"
#include "functions.h"
#include "images.h"

OledMenu::OledMenu(/* args */) {}

OledMenu::~OledMenu() {}

void OledMenu::configLCD() {
  display.init();
  //   display.setFont(DejaVu_Sans_Mono_12);

#ifndef FLIP_DIPLAY
  display.flipScreenVertically();
#endif

  display.clear();
  display.display();
}

void OledMenu::reconnectOledI2C() {
  Wire.begin(SDA_SENSOR_DEFAULT, SCL_SENSOR_DEFAULT);
}

void OledMenu::drawString(int x, int y, String str) {
  display.drawString(x, y, replaceUtf8(str, String(QUESTIONMARK)));
}

void OledMenu::drawString(int row, String str) {
  drawString(0, row * lineHeight, str);
}

void OledMenu::drawLine(int x1, int y1, int x2, int y2) {
  display.drawLine(x1, y1, x2, y2);
}

void OledMenu::drawImage(int16_t xMove, int16_t yMove, int16_t width,
                         int16_t height, const uint8_t *xbm) {
  display.drawXbm(xMove, yMove, width, height, xbm);
}

void OledMenu::drawImageCenter(int16_t width, int16_t height,
                               const uint8_t *xbm) {
  drawImage(screenWidth / 2 - width / 2, sreenHeight / 2 - height / 2, width,
            height, xbm);
}

void OledMenu::drawImageCenterHorizontal(int16_t x, int16_t width,
                                         int16_t height, const uint8_t *xbm) {
  drawImage(x, sreenHeight / 2 - height / 2, width, height, xbm);
}

void OledMenu::drawImageCenterVertical(int16_t y, int16_t width, int16_t height,
                                       const uint8_t *xbm) {
  drawImage(screenWidth / 2 - width / 2, y, width, height, xbm);
}

void OledMenu::setup() {
  reconnectOledI2C();
  configLCD();

  up = new ButtonPullup(BUTTON_UP);
  down = new ButtonPullup(BUTTON_DOWN);
  a = new ButtonPullup(BUTTON_A);

#ifdef ESP32
  left = new ButtonPullup(BUTTON_LEFT);
  right = new ButtonPullup(BUTTON_RIGHT);
#endif

  Serial.println("setup menu and button");

  up->setOnClicked([this]() {
    scrollCounter = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;

    if (currentMenu->selected > 0)
      currentMenu->selected--;
    else
      currentMenu->selected = currentMenu->list->size() - 1;
  });

  up->setOnHolding(
      [this]() {
        scrollCounter = 0;
        scrollTime = currentTime;
        buttonTime = currentTime;
        if (currentMenu->selected > 0)
          currentMenu->selected--;
        else
          currentMenu->selected = currentMenu->list->size() - 1;
      },
      buttonDelay);

  down->setOnClicked([this]() {
    scrollCounter = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;
    if (currentMenu->selected < currentMenu->list->size() - 1)
      currentMenu->selected++;
    else
      currentMenu->selected = 0;
  });

  down->setOnHolding(
      [this]() {
        scrollCounter = 0;
        scrollTime = currentTime;
        buttonTime = currentTime;

        if (currentMenu->selected < currentMenu->list->size() - 1)
          currentMenu->selected++;
        else
          currentMenu->selected = 0;
      },
      buttonDelay);

  a->setOnClicked([this]() {
    scrollCounter = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;
    if (currentMenu->list->get(currentMenu->selected).click) {
      currentMenu->list->get(currentMenu->selected).click();
    }
  });

  a->setOnHolding(
      [this]() {
        scrollCounter = 0;
        scrollTime = currentTime;
        buttonTime = currentTime;
        if (currentMenu->list->get(currentMenu->selected).hold) {
          currentMenu->list->get(currentMenu->selected).hold();
        }
      },
      800);

#ifdef ESP32
  left->setOnClicked([this]() {
    scrollCounter = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;

    if (currentMenu->selected > 0)
      currentMenu->selected--;
    else
      currentMenu->selected = currentMenu->list->size() - 1;
  });

  left->setOnHolding(
      [this]() {
        scrollCounter = 0;
        scrollTime = currentTime;
        buttonTime = currentTime;

        if (currentMenu->selected > 0)
          currentMenu->selected--;
        else
          currentMenu->selected = currentMenu->list->size() - 1;
      },
      800);

  right->setOnClicked([this]() {
    scrollCounter = 0;
    scrollTime = currentTime;
    buttonTime = currentTime;
    if (currentMenu->selected < currentMenu->list->size() - 1)
      currentMenu->selected++;
    else
      currentMenu->selected = 0;
  });

  right->setOnHolding(
      [this]() {
        scrollCounter = 0;
        scrollTime = currentTime;
        buttonTime = currentTime;
        if (currentMenu->selected < currentMenu->list->size() - 1)
          currentMenu->selected++;
        else
          currentMenu->selected = 0;
      },
      800);
#endif

  // changeMenu(&mainMenu);
  startTime = currentTime;
}

void OledMenu::update() {
  // reconnectOledI2C();
  up->update();
  down->update();
  a->update();
#ifdef ESP32
  left->update();
  right->update();
#endif

  if (currentMenu) {
    display.clear();
    drawMenu();
    display.display();
  }
}

void OledMenu::drawMenu() {
  if (currentMenu->isGUI) {
    // display.setFont(DejaVu_Sans_Mono_10);
    drawGUI();

  } else {
    // display.setFont(DejaVu_Sans_Mono_12);
    drawList();
  }
}

void OledMenu::drawList() {
  String tmp;
  int tmpLen;
  int row = (currentMenu->selected / 5) * 5;
  // correct selected if it's off
  if (currentMenu->selected < 0)
    currentMenu->selected = 0;
  else if (currentMenu->selected >= currentMenu->list->size())
    currentMenu->selected = currentMenu->list->size() - 1;

  // draw menu entries
  for (int i = row; i < currentMenu->list->size() && i < row + 5; i++) {
    tmp = currentMenu->list->get(i).getStr();
    tmpLen = tmp.length();
    // horizontal scrolling
    if ((currentMenu->selected == i) && (tmpLen >= maxLen)) {
      tmp = tmp + tmp;
      tmp = tmp.substring(scrollCounter, scrollCounter + maxLen - 1);

      if ((scrollCounter > 0 && scrollTime < currentTime - scrollSpeed) ||
          (scrollCounter == 0 && scrollTime < currentTime - scrollSpeed * 4)) {
        scrollTime = currentTime;
        scrollCounter++;
      }

      if (scrollCounter > tmpLen)
        scrollCounter = 0;
    }

    tmp = (currentMenu->selected == i ? CURSOR : SPACE) + tmp;
    drawString(0, (i - row) * 12, tmp);
  }
}

void OledMenu::drawGUI() {
  if (currentMenu->selected < 0) {
    currentMenu->selected = 0;
  } else if (currentMenu->selected >= currentMenu->list->size()) {
    currentMenu->selected = currentMenu->list->size() - 1;
  }

  int size = currentMenu->list->size();
  int row = (currentMenu->selected);

  if (currentMenu->list->size() > 0) {
    if (row > 0) {
      drawImage(6, 16, default_icon_width, default_icon_height,
                currentMenu->list->get(row - 1).image);
    }

    if (row < size - 1) {
      drawImage(90, 16, default_icon_width, default_icon_height,
                currentMenu->list->get(row + 1).image);
    }

    drawImageCenter(default_icon_width, default_icon_height,
                    currentMenu->list->get(row).image);

    drawString(0, 54, currentMenu->list->get(row).getStr());
  }

  // draw selectbar
  drawImage(46, 14, selectbar_top_width, selectbar_top_height,
            selectbar_top_bits);
  drawImage(46, 42, selectbar_bottom_width, selectbar_bottom_height,
            selectbar_bottom_bits);
}

void OledMenu::clearMenu(Menu *menu) {
  while (menu->list->size() > 0) {
    menu->list->remove(0);
  }
}

void OledMenu::changeMenu(Menu *menu) {
  if (menu) {
    if (currentMenu)
      clearMenu(currentMenu);
    currentMenu = menu;
    buttonTime = currentTime;
    currentMenu->selected = 0;

    if (selectedID < 0)
      selectedID = 0;

    if (currentMenu->parentMenu) {
      addMenuNode(currentMenu, D_BACK, currentMenu->parentMenu); // add
      // [BACK]
      currentMenu->selected = 1;
    }

    if (currentMenu->build) {
      currentMenu->build();
    }
  }
}

void OledMenu::goBack() {
  if (currentMenu->parentMenu)
    changeMenu(currentMenu->parentMenu);
}

void OledMenu::createMenu(Menu *menu, Menu *parent, bool isGUI,
                          std::function<void()> build) {
  menu->list = new SimpleList<MenuNode>;
  menu->parentMenu = parent;
  menu->selected = 0;
  menu->isGUI = isGUI;
  menu->build = build;
}

void OledMenu::addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                           std::function<void()> click,
                           std::function<void()> hold) {
  if (image == NULL) {
    image = menu_exit_bits;
  }
  menu->list->add(MenuNode{image, [ptr]() { return str(ptr); }, click, hold});
}

void OledMenu::addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                           std::function<void()> click) {
  addMenuNode(menu, image, ptr, click, NULL);
}

void OledMenu::addMenuNode(Menu *menu, const uint8_t image[], const char *ptr,
                           Menu *next) {
  addMenuNode(
      menu, image, ptr, [this, next]() { changeMenu(next); }, NULL);
}

void OledMenu::addMenuNode(Menu *menu, std::function<String()> getStr,
                           std::function<void()> click,
                           std::function<void()> hold) {
  menu->list->add(MenuNode{menu_exit_bits, getStr, click, hold});
}

void OledMenu::addMenuNode(Menu *menu, std::function<String()> getStr,
                           std::function<void()> click) {
  addMenuNode(menu, getStr, click, NULL);
}

void OledMenu::addMenuNode(Menu *menu, std::function<String()> getStr,
                           Menu *next) {
  addMenuNode(menu, getStr, [this, next]() { changeMenu(next); });
}

void OledMenu::addMenuNode(Menu *menu, const char *ptr,
                           std::function<void()> click) {
  addMenuNode(
      menu, [ptr]() { return str(ptr); }, click);
}

void OledMenu::addMenuNode(Menu *menu, const char *ptr, Menu *next) {
  addMenuNode(
      menu, [ptr]() { return str(ptr); }, next);
}
