#include "rasterization.h"
#include <iostream>
int main() {
	for (int i = 0; i < 8; i++)
	{
		cube[i].color = 0xFF00FF00;
	}
	//front facing square
	//top left corner
	cube[0] = { -0.25,0.25,0.25,1 };
	//top right corner
	cube[1] = { 0.25,0.25,0.25,1 };
	//bottom left corner
	cube[2] = { -0.25,-0.25,0.25,1 };
	//bottom right corner
	cube[3] = { 0.25,-0.25,0.25,1 };
	//back facing square
	//top left corner
	cube[4] = { -0.25,0.25,-0.25, 1};
	//top right corner
	cube[5] = { 0.25,0.25,-0.25,1 };
	//bottom left corner
	cube[6] = { -0.25,-0.25,-0.25,1 };
	//bottom right corner
	cube[7] = { 0.25,-0.25,-0.25,1 };


	float grid1 = -0.5f;
	for (int i = 0; i < 40; i++)
	{
		grid[i].w = 1;
	}
	for (int i = 0; i < 10; i++)
	{

		grid[i].x = grid1;
		grid[i].y = 0;
		grid[i].z = 0.5;
		grid1 += 0.1f;
	}
	float grid2 = 0.5f;
	for (int i = 10; i < 20; i++)
	{
		grid[i].x = 0.5;
		grid[i].y = 0;
		grid[i].z = grid2;
		grid2 -= 0.1f;
	}
	float grid3 = 0.5f;
	for (int i = 20; i < 30; i++)
	{
		grid[i].x = grid3;
		grid[i].y = 0;
		grid[i].z = -0.5;
		grid3 -= 0.1;
	}
	float grid4 = -0.5f;
	for (int i = 30; i < 40; i++)
	{
		grid[i].x = -0.5;
		grid[i].y = 0;
		grid[i].z = grid4;
		grid4 += 0.1;
	}

	RS_Initialize(RWIDTH, RHEIGHT);
	float degree = 0;
	while (RS_Update(&Raster[0], RPIXELS)) {
		
		clear();
		VertexShader = VS_World;
		VERTEX copyPoints[8] = { 0, };
		for (int i = 0; i < 8; i++)
		{
			copyPoints[i] = cube[i];
		}
		CreateCube(cube, degree);
		for (int i = 0; i < 8; i++)
		{
			cube[i].y = copyPoints[i].y;
		}

		CreateGrid(grid);
		degree = 0.5;
	}

	RS_Shutdown();
	return 0;
}