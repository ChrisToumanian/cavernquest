#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Bitmap
{
public:
  static void saveImageBitmap(char* filename, int w, int h, unsigned char image[1024][1024]);
};

#endif
