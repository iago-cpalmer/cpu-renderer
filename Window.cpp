#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(int r_width, int r_height)
	: m_hInstance(GetModuleHandle(nullptr))
	, m_width(r_width)
	, m_height(r_height)
	, mp_graphic_buffers(nullptr)
{
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + m_width;
	rect.bottom = rect.top + m_height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		style,
		rect.left,
		rect.top,
		m_width,
		m_height,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	m_HDC = GetDC(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {

		switch (msg.message)
		{
			case WM_QUIT:
				{
					return false;
				}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Window::FinishRendering()
{
	HDC hdc = GetDC(m_hWnd);
	HDC hdcBmp = CreateCompatibleDC(hdc);
	HGDIOBJ oldBmp = SelectObject(hdcBmp, mp_graphic_buffers->GetFrontBuffer());

	BitBlt(hdc, 0, 0, mp_graphic_buffers->GetWidth(), mp_graphic_buffers->GetHeight(), hdcBmp, 0, 0, SRCCOPY);

	SelectObject(hdc, oldBmp);
	DeleteDC(hdcBmp);
	ReleaseDC(m_hWnd, hdc);
}

void Window::SetGraphicBuffers(GraphicBuffers* rp_graphic_buffer)
{
	mp_graphic_buffers = rp_graphic_buffer;
}

