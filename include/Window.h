#pragma once
#include "Prerequisites.h"

class
Window{
	public:
		Window();
		~Window();

		HRESULT
		init(HINSTANCE hInstance, int nCndShow, WNDPROC wndproc, LPCSTR windowName);

		void 
		update();
		void 
		render();
		void 
		destroy();

public:
	//It can be useful to manipulate a window associated with a console application.
	HWND m_hWnd = nullptr;
	//Mark the identifier as null
	HINSTANCE n_hInst = nullptr;
	//used to create rectangles
	RECT m_rect;
	//The width of the window is instantiated
	unsigned int m_width;
	//The heigh of the window is instantiated
	unsigned int m_height;
	//The name of the window is instantiated
	LPCSTR m_windowName = "None";
};
