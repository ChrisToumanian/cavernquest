#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "console.h"
#include "cave.h"

using namespace std;

class Player
{
public:
  Player();
  string name = "wanderer";
  char symbol = '@';
  unsigned char forecolor = 15;
  unsigned char backcolor = 0;
  int posX = 512;
  int posY = 512;
  int health = 100;
  Cave* cave;
  Console* console;

  void update();
  void command(char command);
  void move(int moveX, int moveY);
  void touchTile();
  void touchTile(Tile* tile);
  void dig(Tile* tile);
  void changeHealth(int amount);
  void die(string message);
  void explore();
  void quit();
};

#endif
