#include "cave.h"

Cave::Cave()
{
}

void Cave::update()
{
}

void Cave::save()
{
  ofstream file("cave.dat");

  if (file.fail()) return;

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      file << map[x][y]->id << map[x][y]->state << map[x][y]->explored;
    }
  }
}

void Cave::loadSettings()
{
  ifstream file("settings.yml");
  string line;
  srand(seed);
  
  if (file.good())
  {
    while (getline(file, line)) {
      if (line.length() > 1 && line[0] != '#')
      {
        string key = line.substr(0, line.find(": "));
        string value = line.substr(line.find(": ") + 2, line.length() - line.find(": ") - 3);
        if (key == "difficulty")
          difficulty = value;
        if (key == "seed")
          seed = stoi(value);
      }
    }
  }
}

void Cave::loadMap()
{
  ifstream f("cave.dat", fstream::in);

  if (f.good())
  {
    char ch;
    allocate();
    for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
      {
        f >> noskipws >> ch;
        map[x][y]->id = ch;
        f >> noskipws >> ch;
        map[x][y]->state = ch;
        f >> noskipws >> ch;
        map[x][y]->explored = ch;
      }
    }
  }
  else
  {
    srand(seed);
    allocate();
    generate();
    save();
  }
}

void Cave::allocate()
{
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
        Tile* tile = new Tile();
        map[x][y] = tile;
    }
  }
}

void Cave::generate()
{
  fillWithRock();
  fillClump(512, 512, 1, 0, 5);
  disperseClumps(20, 20, width - 20, height - 20, 1, 0, 700, 4, 8);
  disperseClumps(20, 20, width - 20, height - 20, 4, 0, 500, 3, 4);
  fillDirtPattern();
}

void Cave::disperseClumps(int x, int y, int w, int h, int id, int state, int amount, int radiusMin, int radiusMax)
{
  for (int i = 0; i < amount; i++)
  {
    fillClump(rand() % (x + w) + x, rand() % (y + h) + y, id, state, rand() % radiusMax + radiusMin);
  }
}

void Cave::fillClump(int x, int y, int id, int state, int radius)
{
  for (int i = 0; i < (radius + (radius / 2)); i++)
  {
    vector<Tile*> tiles = getTileClump(x + i, y, radius);
    for(Tile* tile : tiles)
    {
      tile->id = id;
      tile->state = state;
    }
  }
}

void Cave::fillWithRock()
{
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      int state = rand() % 5;
      map[x][y]->id = 3;
      map[x][y]->state = 0;
      map[x][y]->explored = 0;
    }
  }
}

void Cave::fillDirtPattern()
{
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      if (map[x][y]->id == 1)
      {
	int n = rand() % 20;
	if (n == 1)
	{
	  map[x][y]->id = 2;
	  map[x][y]->state = 0;
	}
	else
	{
	  map[x][y]->state = 0;
	}
      }
    }
  }
}

void Cave::disperseTile(int id, int state, int chance, int xPos, int yPos, int w, int h)
{
  for (int x = xPos; x < xPos + w; x++)
  {
    for (int y = yPos; y < yPos + h; y++)
    {
      int n = rand() % chance + 0;
      if (n == 1)
      {
	map[x][y]->id = id;
	map[x][y]->state = id;
      }
    }
  }
}

bool Cave::tileExists(int x, int y)
{
  if (x < 0 || y < 0 || x > width - 1 || y > height - 1)
    return false;
  return true;
}

void Cave::setTileExplored(int x, int y)
{
  if (tileExists(x, y))
    map[x][y]->explored = 1;
}

bool Cave::tileIsPhysical(int x, int y)
{
  if (!tileExists(x, y))
    return true;

  if (map[x][y]->id == 3)
    return true;
  
  return false;
}

char Cave::getTileSymbol(int x, int y)
{
  Tile* tile = map[x][y];
  if (tile->id == 1)
    return '.';
  else if (tile->id == 2 && tile->state == 0)
    return 'o';
  else if (tile->id == 3 && tile->state == 1)
    return '#';
  return ' ';
}

unsigned char Cave::getTileColor(int x, int y)
{
  Tile* tile = map[x][y];
  if (tile->id == 1 || tile->id == 2)
    return 2;
  if (tile->id == 3)
    return 3;
  if (tile->id == 4)
    return 4;
  return 1;
}

vector<Tile*> Cave::getTileClump(int x, int y, int radius)
{
  vector<Tile*> tiles;
  
  for (int x2 = x - radius; x2 < x + radius; x2++)
  {
    for (int y2 = y - radius; y2 < y + radius; y2++)
    {
      if (getDistance(x, y, x2, y2) < radius && tileExists(x2, y2))
	      tiles.push_back(map[x2][y2]);
    }
  }

  return tiles;
}

int Cave::getDistance(int x1, int y1, int x2, int y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void Cave::saveMapBitmap()
{
  unsigned char image[width][height];

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      image[x][y] = map[x][y]->id * 80;
    }
  }
  
  Bitmap::saveImageBitmap("cave.bmp", width, height, image);
}
