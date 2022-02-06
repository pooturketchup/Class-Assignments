#include "Defines.h"
#include "shaders.h"
#include "RasterSurface.h"



#pragma once

void FillTriangle(VERTEX a, VERTEX b, VERTEX c, int i) {
	const unsigned int white = 0xFFFFFFFF;

	
	VertexShader(a, i);
	VertexShader(b, i);
	VertexShader(c, i);

	
	//loop over every pixel's x & y

	for (int x = 0; x < RWIDTH; x++) {
		for (int y = 0; y < RHEIGHT; y++) {
			VEC_3D bary = FindBarycentric(a, b, c, { x * 1.0F, y * 1.0F });
			if (bary.x < 0 || bary.x > 1 || bary.y < 0 || bary.y > 1 || bary.z < 0 || bary.z > 1)
				continue;

			unsigned int colorChange = PixelShader(a,b,c,bary);

				PlotPixel(x, y, colorChange);
		}
	}

	Bresenham(a.pos[0], b.pos[0], a.pos[1], b.pos[1], white);
	Bresenham(b.pos[0], c.pos[0], b.pos[1], c.pos[1], white);
	Bresenham(c.pos[0], a.pos[0], c.pos[1], a.pos[1], white);
}

void clear() {
	for (int i = 0; i < RWIDTH; i++) {
		for (int j = 0; j < RHEIGHT; j++) {
			PlotPixel(i, j, 0xFF000000);
		}
	}
}
