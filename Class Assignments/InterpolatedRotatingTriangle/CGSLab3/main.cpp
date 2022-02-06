#include "Draw.h"

int main(){
	//Draw* image = new Draw;
	//float arrays
	float AValues[4] = { 700,900,0,0 }; 
	float BValues[4] = { 800, 400, 0, 0 };
	float CValues[4] = { 400, 400, 0, 0 };

	VERTEX A = { *AValues, 0xFF0000FF };
	VERTEX B = { *BValues,  0xFFFF0000 };
	VERTEX C = { *CValues,  0xFF00FF00 };
	//fill in information
	A.pos[0] = AValues[0];
	A.pos[1] = AValues[1];
	A.pos[2] = AValues[2];
	A.pos[3] = AValues[3];
	A.color = 0xFF0000FF;
	points[0] = A;
	B.pos[0] = BValues[0];
	B.pos[1] = BValues[1];
	B.pos[2] = BValues[2];
	B.pos[3] = BValues[3];
	B.color = 0xFFFF0000;
	points[1] = B;
	C.pos[0] = CValues[0];
	C.pos[1] = CValues[1];
	C.pos[2] = CValues[2];
	C.pos[3] = CValues[3];
	C.color = 0xFF00FF00;
	points[2] = C;

	RS_Initialize(RWIDTH, RHEIGHT);

	const unsigned int white = 0xFFFFFFFF;
	int i = 0;

	while (RS_Update(&Raster[0], RPIXELS)) {
		clear();
		//fill in triangle and update positions
		VertexShader = VS_Rotation;
		PixelShader = PS_ColorLerp;
		FillTriangle(points[0], points[1], points[2], i);
		i++;
	}

	RS_Shutdown();
	return 0;
}