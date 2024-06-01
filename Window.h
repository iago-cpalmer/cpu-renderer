#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {

public:
	// Constants
	const wchar_t* CLASS_NAME = L"My own renderer";
	const wchar_t* WINDOW_NAME = L"We rendering a cool empty triangle";
	// Variables
	int width = 640, height = 480;
	// Functions
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void SetPixelAt(int x, int y, COLORREF color);
	bool InsideWindowBounds(int x, int y);

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_HDC;
};

#endif // !WINDOW_H
