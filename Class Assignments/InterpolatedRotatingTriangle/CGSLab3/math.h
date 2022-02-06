
#include "Defines.h"
#pragma once
void PlotPixel(int x, int y, unsigned int color) {
	Raster[RWIDTH * y + x] = color;
}
//math functions
float ImplicitLine(VERTEX a, VERTEX b, VERTEX p) {
	//Ax +  By + C = 0
	//(Y1 - Y2)x + (X2 - X1)y + X1Y2 - Y1X2 = 0

	return (a.pos[1] - b.pos[1]) * (p.pos[0]) + (b.pos[0] - a.pos[0]) * (p.pos[1]) + a.pos[0] * b.pos[1] - a.pos[1] * b.pos[0];
	//(a.y - b.y) * p.x + (b.x - a.x) * p.y + a.x * b.y - a.y * b.x;
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
VEC_3D FindBarycentric(VERTEX a, VERTEX b, VERTEX c, VERTEX p)
{
	float maxA = ImplicitLine(b, c, a);
	float subA = ImplicitLine(b, c, p);

	float maxB = ImplicitLine(a, c, b);
	float subB = ImplicitLine(a, c, p);

	float maxC = ImplicitLine(b, a, c);
	float subC = ImplicitLine(b, a, p);

	return { subA / maxA, subB / maxB, subC / maxC };
}

VERTEX NDCToScreen(VERTEX change) {
	change.pos[0] = (change.pos[0] / RWIDTH + 1) * (RWIDTH / 2);
	change.pos[1] = (1 - change.pos[1] / RHEIGHT) * (RHEIGHT / 2);
	return change;
}

void FindWeight(VERTEX a, VERTEX b, VERTEX c, int p_x, int p_y, float& weight1, float& weight2, float& weight3) {
	weight1 = ((b.pos[1] - c.pos[1]) * (p_x - c.pos[0]) + (c.pos[0] - b.pos[0]) * (p_y - c.pos[1])) / static_cast<float>(((b.pos[1] - c.pos[1]) * (a.pos[0] - c.pos[0]) + (c.pos[0] - b.pos[0]) * (a.pos[1] - c.pos[1])));//((y_v1 - y_v2) * (p_x - x_v2) + (x_v2 - x_v1) * (p_y - y_v2)) / static_cast<float>(((y_v1 - y_v2) * (x_v1 - x_v2) + (x_v2 - x_v1) * (y_v1 - y_v2)));
	weight2 = ((c.pos[1] - a.pos[1]) * (p_x - c.pos[0]) + (a.pos[0] - c.pos[0]) * (p_y - c.pos[1])) / static_cast<float>(((b.pos[1] - c.pos[1]) * (a.pos[0] - c.pos[0]) + (c.pos[0] - b.pos[0]) * (a.pos[1] - c.pos[1])));//((y_v1 - y_v2) * (p_x - x_v2) + (x_v2 - x_v1) * (p_y - y_v2)) / static_cast<float>(((y_v1 - y_v2) * (x_v1 - x_v2) + (x_v2 - x_v1) * (y_v1 - y_v2)));
	weight3 = 1 - weight1 - weight2;
}