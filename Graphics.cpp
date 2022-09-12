#include "pch.h"
#include "Graphics.h"




int Graphics::Init() {
	glPushMatrix();
	GLfloat tmp_viewport[4];
	glGetFloatv(GL_VIEWPORT, tmp_viewport);

	glViewport(0, 0, tmp_viewport[2], tmp_viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, tmp_viewport[2], tmp_viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return 0;

}



Graphics::Graphics(HWND overLayhandle, int sWidth, int sHeight) : windowWidth(sWidth), windowHeight(sHeight)
{
	
}

Graphics::~Graphics()
{


}


int Graphics::BeginScene()
{
	return 0;

}


int Graphics::EndScene()
{


	return 0;
}


void Graphics::drawText(char* String, int x, int y, COLOR color)
{

}


void Graphics::DrawLine(int x1, int y1, int x2, int y2,  float px , COLOR color)
{
	Init();
	glColor3ub(color.R, color.G, color.B);
	glLineWidth(px);


	int line[4] = {x1,y1,x2,y2};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer( 2 , GL_INT, 0, line);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

}


void Graphics::DrawBox(int x, float y, int width, int height, int px, COLOR color)
{
	Vector2 points[4];
	points[0] = { (float)x, (float)y };
	points[1] = { (float)(x + width), (float)y };
	points[2] = { (float)(x + width), (float)(y + height) };
	points[3] = { (float)x, (float)(y + height) };

	Init(); 
	glColor3ub(color.R , color.G , color.B);
	glLineWidth(px);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, points);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}