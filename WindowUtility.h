#pragma once


namespace WindowUtil
{
	struct WINDOW_ATT
	{
		int x;
		int y;
		int width;
		int height;
	};
	RECT getWindowRectEx(HWND handle);
	RECT getWindowRect(HWND handle);
	WINDOW_ATT  getWindowAtt(HWND handle);
}

