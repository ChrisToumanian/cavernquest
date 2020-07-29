#ifndef GAME_H
#define GAME_H

#include <string>
#include "cave.h"
#include "player.h"
#include "console.h"

using namespace std;

static bool running = false;

class Game
{
public:
  Game();
  Console* console;
  Player* player;
  Cave* cave;

  void play();
  void loop();
  void draw();
  void showWelcomeScreen();
};

#endif