#pragma once
#include "shaders.h"

void clear() {
	for (int i = 0; i < RWIDTH; i++) {
		for (int j = 0; j < RHEIGHT; j++) {
			PlotPixel(i, j, 0xFF000000);
		}
	}
}

void CreateCube(VERTEX change[], float degree) {

	float cos = cosf(degree * (PI / 180.0F));
	float sin = sinf(degree * (PI / 180.0F));
	float YRotation[16]{ //world
		cos, 0, sin, 0,
		0,1,0, 0,
		-sin, 0, cos, 0,
		0,0.25,0,1
	};
	float View[16]{ //view 
		1, 0, 0, 0,
		0, cosf(-18 * (PI / 180)), -sinf(-18 * (PI / 180)), 0,
		0 , sinf(-18 * (PI / 180)), cosf(-18 * (PI / 180)), 0,
		0,-0.5,-1,1
	};
	float Yscale = 1 / tanf(45 * (PI / 180.0F));
	float Xscale = Yscale * 1;
	float zNear = 0.1;
	float zFar = 10.0;
	float projectionView[16] =
	{
		Xscale,0,0,0,
		0,Yscale,0,0,
		0,0,zFar / (zFar - zNear),1,
		0,0,-(zFar * zNear) / (zFar - zNear),0
	};

	unsigned int green = 0xFF00FF00;
	for (int i = 0; i < 8; i++)
	{

		VERTEX p = VertexShader(cube[i], YRotation, View, projectionView);
		float perspective[16]{
			1/p.w, 0,0,0,
			0, 1/p.w, 0,0,
			0,0, 1/p.w,0,
			0,0,0,1
		};
		p = Matrix4x4Math(p, perspective);
		p = NDCToScreen(p);

		copyPoints[i] = p;
	}
	////front
	Bresenham(copyPoints[0].x, copyPoints[1].x, copyPoints[0].y, copyPoints[1].y, green);
	Bresenham(copyPoints[0].x, copyPoints[2].x, copyPoints[0].y, copyPoints[2].y,green);
	Bresenham(copyPoints[2].x, copyPoints[3].x, copyPoints[2].y, copyPoints[3].y,green);
	Bresenham(copyPoints[3].x, copyPoints[1].x, copyPoints[3].y, copyPoints[1].y,green);
	//back
	Bresenham(copyPoints[4].x, copyPoints[5].x, copyPoints[4].y, copyPoints[5].y, green);
	Bresenham(copyPoints[4].x, copyPoints[6].x, copyPoints[4].y, copyPoints[6].y, green);
	Bresenham(copyPoints[6].x, copyPoints[7].x, copyPoints[6].y, copyPoints[7].y, green);
	Bresenham(copyPoints[5].x, copyPoints[7].x, copyPoints[5].y, copyPoints[7].y, green);
	//top
	Bresenham(copyPoints[0].x, copyPoints[4].x, copyPoints[0].y, copyPoints[4].y, green);
	Bresenham(copyPoints[1].x, copyPoints[5].x, copyPoints[1].y, copyPoints[5].y, green);
	//bottom
	Bresenham(copyPoints[2].x, copyPoints[6].x, copyPoints[2].y, copyPoints[6].y, green);
	Bresenham(copyPoints[3].x, copyPoints[7].x, copyPoints[3].y, copyPoints[7].y, green);
}

void CreateGrid(VERTEX change[]) {
	VERTEX copyGrid[40];
	float worldMatrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	float View[16]{ 
		1, 0, 0, 0,
		0, cosf(-18 * (PI / 180)), -sinf(-18 * (PI / 180)), 0,
		0 , sinf(-18 * (PI / 180)), cosf(-18 * (PI / 180)), 0,
		0,0,-1,1
	};
	float Yscale = 1 / tanf(45 * (PI/180.0F));
		float Xscale = Yscale * 1;
		float zNear = 0.1;
		float zFar = 10.0;
		float projectionView[16] =
		{
			Xscale,0,0,0,
			0,Yscale,0,0,
			0,0,zFar / (zFar - zNear),1,
			0,0,-(zFar * zNear) / (zFar - zNear),0
		};
	for (int i = 0; i < 40; i++)
	{
		
		VERTEX p = VertexShader(grid[i], worldMatrix, View, projectionView);

		float perspective[16]{
			1 / p.w, 0,0,0,
			0, 1 / p.w, 0,0,
			0,0, 1 / p.w,0,
			0,0,0,1
		};
		p = Matrix4x4Math(p, perspective);
		p = NDCToScreen(p);
		copyGrid[i] = p;
	}
	for (int i = 0; i < 11; i++)
	{
		Bresenham(copyGrid[i].x, copyGrid[30-i].x, copyGrid[i].y, copyGrid[30-i].y, 0xFFFFFFFF);
	}
	for (int i = 11; i < 21; i++)
	{
		Bresenham(copyGrid[i].x, copyGrid[50 - i].x, copyGrid[i].y, copyGrid[50 - i].y, 0xFFFFFFFF);
	}
	Bresenham(copyGrid[10].x, copyGrid[0].x, copyGrid[10].y, copyGrid[0].y, 0xFFFFFFFF);
}
