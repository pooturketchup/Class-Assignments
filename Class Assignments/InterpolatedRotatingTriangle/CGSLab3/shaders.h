#include <iostream>
#include "math.h"
#pragma once
void (*VertexShader)(VERTEX&, int&) = nullptr;
unsigned int (*PixelShader)(VERTEX&, VERTEX&, VERTEX&, VEC_3D&) = nullptr;
unsigned int (*ColorLerp)(unsigned int&, unsigned int&, float&) = nullptr;
void VS_Rotation(VERTEX& change, int& i) {

	float cos = cosf(i * (PI / 180.0F));
	float sin = sinf(i * (PI / 180.0F));

	//find the center of the triangle
	float centerX = (points[0].pos[0] + points[1].pos[0] + points[2].pos[0]) / 3;
	float centerY = (points[0].pos[1] + points[1].pos[1] + points[2].pos[1]) / 3;
	VERTEX center;
	center.pos[0] = centerX;
	center.pos[1] = centerY;

	float x = change.pos[0] - centerX;
	float y = change.pos[1] - centerY;

	change.pos[0] = cos * x - sin * y;
	change.pos[1] = sin * x + cos * y;

	change = NDCToScreen(change);
}
unsigned PS_ColorLerp(VERTEX& a, VERTEX& b, VERTEX& c, VEC_3D& bary) {
	int red = ((b.color >> 16) & 0xFF) * bary.x;
	int green = ((c.color >> 8) & 0xFF) * bary.y;
	int blue = (a.color & 0xFF) * bary.z;
	unsigned colorChange = (red << 16) + (green << 8) + blue;
	return colorChange;
}
