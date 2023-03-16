#include "Viewport.h"
#include "Window.h"

//refers to the part of the document you are viewing, which is currently visible in your window
void
Viewport::init(Window window) {

    //In the event that windows is found to be null, the following message will be displayed
    if (window.m_hWnd == nullptr) {
        WARNING("ERROR: Viewport::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Window window] \n");
        exit(1);
    }
    
    //It adjusts the width
    m_viewport.Width = (FLOAT)window.m_width;
    //It adjusts the height
    m_viewport.Height = (FLOAT)window.m_height; 
    //Its minimum depth is adjusted
    m_viewport.MinDepth = 0.0f;
    //Its maximum depth is adjusted
    m_viewport.MaxDepth = 1.0f;
    //The stop is set on the vector x
    m_viewport.TopLeftX = 0;
    //the stop is set on the vector and
    m_viewport.TopLeftY = 0;
}

void
Viewport::update() {
}

void
Viewport::render() {
}

void
Viewport::destroy() {
}