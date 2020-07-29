#include "game.h"

using namespace std;

Game* game;

int main(int argc, char *argv[])
{
  // Create new game
  game = new Game();

  // Play game
  game->play();

  return 0;
}
