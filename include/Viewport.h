#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"



//The Window class is called to use its variables
class
	Window;

class
	DeviceContext;

//Create the camera's point of view class
class
	Viewport {
public:
	Viewport() = default;
	~Viewport() {};

	//Defines the dimensions of a viewport 
	void
	init(Window window);

	void
  update();

	void
	render(DeviceContext& deviceContext);

	void
	destroy();

public:
	//Defines the dimensions of a viewport.
	D3D11_VIEWPORT m_viewport;
};