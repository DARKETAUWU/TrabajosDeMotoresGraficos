#pragma once
#include "Prerequisites.h"

class
Window{
	public:
		Window();
		~Window();

		HRESULT
			init(HINSTANCE hInstance, int nCndShow, WNDPROC wndproc);

		void update();
		void render();
		void destroy();

public:
	HWND m_hWnd = nullptr;
	HINSTANCE n_hInst = nullptr;
	RECT m_rect;
	unsigned int m_width;
	unsigned int m_height;
	LPCSTR m_windowName = "None";
};
