#include "pch.h"
#include "WindowUtility.h"

RECT WindowUtil::getWindowRectEx(HWND handle)
{
	RECT sRect, pRect;
	GetClientRect(handle, &sRect);
	GetWindowRect(handle, &pRect);

	pRect.top = pRect.bottom - sRect.bottom;

	return pRect;
}

RECT WindowUtil::getWindowRect(HWND handle)
{
	RECT wRect;
	GetClientRect(handle, &wRect);

	return wRect;
}


WindowUtil::WINDOW_ATT WindowUtil::getWindowAtt(HWND handle)
{
	RECT wRect = getWindowRect(handle);

	WINDOW_ATT windowAtt;
	windowAtt.x = wRect.left;
	windowAtt.y = wRect.top;
	windowAtt.width = wRect.right - wRect.left;
	windowAtt.height = wRect.bottom - wRect.top - 26;

	return windowAtt;
}