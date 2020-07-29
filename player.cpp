#include "player.h"

Player::Player()
{
}

void Player::update()
{
  touchTile();
  command(console->getChar());
  explore();
}

void Player::command(char command)
{
  if (command == 'q')
    quit();
  else if (command == 'w')
    move(0, 1);
  else if (command == 'a')
    move(-1, 0);
  else if (command == 's')
    move(0, -1);
  else if (command == 'd')
    move(1, 0);
}

void Player::move(int x, int y)
{
  touchTile(cave->map[posX + x][posY + y]);
  
  if (!cave->tileIsPhysical(posX + x, posY + y))
  {
    posX += x;
    posY += y;
  }
}

void Player::touchTile()
{
  if (cave->map[posX][posY]->id == 4) // Lava
  {
    die("You have fallen into lava and died.");
  }
  else if (cave->map[posX][posY]->id == 0) // Void
  {
    die("You have fallen into the void.");
  }
}

void Player::touchTile(Tile* tile)
{
  if (tile->id == 3) // Rock
    dig(tile);
}

void Player::dig(Tile* tile)
{
  if (tile->state == 0) // Solid rock
  {
    tile->state = 1;
  }
  else if (tile->state == 1) // Broken rock
  {
    tile->id = 1;
    tile->state = 0;
  }
}

void Player::changeHealth(int amount)
{
  health += amount;
  if (health > 100)
    health = 100;
  else if (health < 1)
    die("You have died.");
}

void Player::die(string message)
{
  health = 0;
  console->printString(0, 0, " Health: " + to_string(health));
  console->printString(0, 32, " Press any key to exit game.                 ");
  console->printString(20, 15, message);
  console->update();
  console->getChar();
  quit();
}

void Player::explore()
{
  cave->setTileExplored(posX, posY);
  cave->setTileExplored(posX + 1, posY);
  cave->setTileExplored(posX - 1, posY);
  cave->setTileExplored(posX, posY + 1);
  cave->setTileExplored(posX, posY - 1);
  cave->setTileExplored(posX + 1, posY + 1);
  cave->setTileExplored(posX - 1, posY - 1);
  cave->setTileExplored(posX + 1, posY - 1);
  cave->setTileExplored(posX - 1, posY + 1);

  cave->setTileExplored(posX - 1, posY + 2);
  cave->setTileExplored(posX, posY + 2);
  cave->setTileExplored(posX + 1, posY + 2);

  cave->setTileExplored(posX - 1, posY - 2);
  cave->setTileExplored(posX, posY - 2);
  cave->setTileExplored(posX + 1, posY - 2);

  cave->setTileExplored(posX + 2, posY - 1);
  cave->setTileExplored(posX + 2, posY);
  cave->setTileExplored(posX + 2, posY + 1);

  cave->setTileExplored(posX - 2, posY - 1);
  cave->setTileExplored(posX - 2, posY);
  cave->setTileExplored(posX - 2, posY + 1);


  cave->setTileExplored(posX + 3, posY - 1);
  cave->setTileExplored(posX + 3, posY);
  cave->setTileExplored(posX + 3, posY + 1);

  cave->setTileExplored(posX - 3, posY - 1);
  cave->setTileExplored(posX - 3, posY);
  cave->setTileExplored(posX - 3, posY + 1);

  
  cave->setTileExplored(posX + 4, posY - 1);
  cave->setTileExplored(posX + 4, posY);
  cave->setTileExplored(posX + 4, posY + 1);

  cave->setTileExplored(posX - 4, posY - 1);
  cave->setTileExplored(posX - 4, posY);
  cave->setTileExplored(posX - 4, posY + 1);
}

void Player::quit()
{
  cave->save();
  console->exitGame();
}
