#include "game.h"

Game::Game()
{
}

void Game::play()
{
  cave = new Cave();
  player = new Player();
  console = new Console();
  player->cave = cave;
  player->console = console;
  running = true;

  showWelcomeScreen();
  cave->saveMapBitmap();
  player->explore();
  
  while(running)
  {
    loop();
  }
}

void Game::loop()
{
  draw();
  player->update();
  cave->update();
}

void Game::draw()
{
  console->clear();
  
  // Draw map
  for (int y = player->posY - 15; y < player->posY + 15; y++)
  {
    for (int x = player->posX - 39; x < player->posX + 39; x++)
    {
      if (cave->tileExists(x, y) && cave->map[x][y]->explored)
      {
        console->printCharColorOffset(x, -y, 40 - player->posX, 15 + player->posY, cave->getTileSymbol(x, y), cave->getTileColor(x, y));
      }
    }
  }

  // Draw player
  console->printChar(40, 15, player->symbol);
  
  // Write status
  console->printString(0, 0, " Health: " + to_string(player->health));
  console->printString(0, 32, " " + cave->description);

  console->update();
}

void Game::showWelcomeScreen()
{
  // Title
  console->printString(40, 5, "CAVERN QUEST");
  console->printString(25, 10, "Explore the entire cavern. Death is final.");
  console->printString(35, 20, "Generating cave...");
  console->update();

  // Load Cave
  cave->loadSettings();
  cave->loadMap();

  // Begin quest
  console->printString(29, 20, "Press any key to begin your quest.");
  console->update();
  console->getChar();
  console->clear();
  console->update();
}
