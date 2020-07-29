#ifndef CAVE_H
#define CAVE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include<cmath>
#include "bitmap.h"

using namespace std;

struct Tile
{
  unsigned char id = 1;
  unsigned char state = 0;
  unsigned char explored = 1;
};

class Cave
{
public:
  Cave();
  const static int width = 1024;
  const static int height = 1024;
  int seed = 27;
  Tile* map[width][height];
  bool monsters = true;
  string difficulty = "normal";
  string description = "It is dark. You feel a chill.";

  void allocate();
  void generate();
  void update();
  void save();
  void loadMap();
  void loadSettings();
  bool tileExists(int x, int y);
  bool tileIsPhysical(int x, int y);
  void setTileExplored(int x, int y);
  char getTileSymbol(int x, int y);
  unsigned char getTileColor(int x, int y);
  void disperseClumps(int x, int y, int w, int h, int id, int state, int amount, int radiusMin, int radiusMax);
  void fillClump(int x, int y, int id, int state, int radius);
  void fillWithRock();
  void fillDirtPattern();
  void disperseTile(int id, int state, int chance, int xPos, int yPos, int w, int h);
  vector<Tile*> getTileClump(int x, int y, int radius);
  int getDistance(int x1, int y1, int x2, int y2);
  void saveMapBitmap();
};

#endif
