#pragma once


#define RED Graphics::COLOR{255,0,0}
#define WHITE Graphics::COLOR{255,255,255}
#define GREEN Graphics::COLOR{0,255,0}



class Graphics {
private:

private:
	int Init();



public:
	struct COLOR {
		int R;
		int G;
		int B;
	};

	int windowWidth, windowHeight = 0;


public:
	Graphics(HWND overLayhandle, int sWidth, int sHeight);
	~Graphics();
	int BeginScene();

	void drawText(char* String, int x, int y, COLOR color);
	void DrawLine(int x1, int y1, int x2, int y2,float px , COLOR color);
	void DrawBox(int x, float y, int width, int height, int px, COLOR color);

	int EndScene();
};