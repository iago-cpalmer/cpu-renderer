#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "GraphicsBuffer.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {

public:
	// --------------------------------
	// Constants
	// --------------------------------

	const wchar_t* CLASS_NAME = L"My own renderer";
	const wchar_t* WINDOW_NAME = L"We rendering a cool empty triangle";

	// --------------------------------
	// Functions
	// --------------------------------

	Window(int r_width, int r_height);
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void FinishRendering();

	void SetGraphicBuffers(GraphicBuffers* rp_graphic_buffer);

private:

	// --------------------------------
	// Variables
	// --------------------------------
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_HDC;

	int m_width, m_height;

	GraphicBuffers* mp_graphic_buffers;
};

#endif // !WINDOW_H
