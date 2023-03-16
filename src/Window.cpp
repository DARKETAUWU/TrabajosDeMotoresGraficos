//The Window library is called, which has several libraries that will be used throughout the project.
#include "Window.h"

Window::Window() {

}

Window::~Window() {

}

//Initializes a thread to use Windows Runtime APIs.
HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc){

    //Contains window class information. It is used with the RegisterClassEx and GetClassInfoEx  functions
    WNDCLASSEX wcex; 
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndproc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow("TutorialWindowClass", "Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!m_hWnd)
        return E_FAIL;

    //Controls how the window is to be shown.
    ShowWindow(m_hWnd, nCmdShow);

    //Retrieves the coordinates of a window's client area. The client coordinates specify the upper-left and lower-right corners of the client area.
    GetClientRect(m_hWnd, &m_rect);
    m_width = m_rect.right - m_rect.left;
    m_height = m_rect.bottom - m_rect.top;
    return S_OK;
}

void 
Window::update(){

}

void 
Window::render() {

}

void 
Window::destroy() {

}