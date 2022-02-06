#pragma once
#define RWIDTH 500
#define RHEIGHT 500
#define RPIXELS ((RWIDTH)*(RHEIGHT))
#define PI 3.1415926
struct VEC_2D {
	float x, y;
};
struct VERTEX {
	float pos[4];
	unsigned int color;
};
struct VEC_3D {
	float x, y, z;
};
unsigned int Raster[RPIXELS] = { 0, };

VERTEX points[3];