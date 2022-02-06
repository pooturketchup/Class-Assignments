#pragma once
#include "math.h"

VERTEX (*VertexShader)(VERTEX& , float[], float[], float[]) = nullptr;

VERTEX VS_World(VERTEX& p, float world[], float view[], float projection[]) {
	VERTEX World = Matrix4x4Math(p, world);
	VERTEX View = Inverse(World, view);
	VERTEX Projection = Matrix4x4Math(View, projection);
	return Projection;
}

