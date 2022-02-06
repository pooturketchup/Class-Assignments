#pragma once
#include "Defines.h"
void PlotPixel(int x, int y, unsigned int color) {
	Raster[RWIDTH * y + x] = color;
}
void Bresenham(int x1, int x2, int y1, int y2, unsigned int color) {
	int posX = abs(x2 - x1);
	int addx = x1 < x2 ? 1 : -1;
	int posY = -abs(y2 - y1);
	int addy = y1 < y2 ? 1 : -1;
	int posT = posX + posY;
	int error = 0;

	while (true) {
		PlotPixel(x1, y1, color);
		if (x1 == x2 && y1 == y2) {
			break;
		}
		error = 2 * posT;
		if (error >= posY) {
			posT += posY;
			x1 += addx;
		}
		if (error <= posX) {
			posT += posX;
			y1 += addy;
		}
	}
}

VERTEX NDCToScreen(VERTEX change) {
	change.x = (change.x  + 1) * (RWIDTH / 2);
	change.y = (1 - change.y) * (RHEIGHT / 2);
	return change;
}

VERTEX Matrix4x4Math(VERTEX& change, float matrix[]) {

	float x = change.x * matrix[0] + change.y * matrix[4] + change.z * matrix[8] + change.w * matrix[12];
	float y = change.x * matrix[1] + change.y * matrix[5] + change.z * matrix[9] + change.w * matrix[13];
	float z = change.x * matrix[2] + change.y * matrix[6] + change.z * matrix[10] + change.w * matrix[14];
	float w = change.x * matrix[3] + change.y * matrix[7] + change.z * matrix[11] + change.w * matrix[15];
	change.x = x;
	change.y = y;
	change.z = z;
	change.w = w;

	return change;
}

VERTEX Inverse(VERTEX& change, float matrix[]) {
    float m[16] =
    {
        matrix[0], matrix[4], matrix[8], matrix[3],
        matrix[1], matrix[5], matrix[9], matrix[7],
        matrix[2], matrix[6], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]
    };

    float x = change.x * m[0] + change.y * m[4] + change.z * m[8]+ change.w * m[12];
    float y = change.x * m[1] + change.y * m[5] + change.z * m[9]+ change.w * m[13];
    float z = change.x * m[2] + change.y * m[6] + change.z * m[10]+ change.w * m[14];
	float w = change.x * m[3] + change.y * m[7] + change.z * m[11] + change.w * m[15];

    change.x = -x;
    change.y = -y;
    change.z = -z;
	change.w = -w;

    return change;
}

