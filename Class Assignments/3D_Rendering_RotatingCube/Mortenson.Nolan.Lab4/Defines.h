#pragma once
#include "RasterSurface.h"
#include <iostream>
#define RWIDTH 500
#define RHEIGHT 500
#define RPIXELS ((RWIDTH)*(RHEIGHT))
#define PI 3.1415926
//8 vertex 12 lines
struct VERTEX {
	float x, y, z, w;
	unsigned int color;
};

unsigned int Raster[RPIXELS] = { 0, };
VERTEX copyPoints[8] = { 0 };

VERTEX cube[8];

VERTEX grid[40];