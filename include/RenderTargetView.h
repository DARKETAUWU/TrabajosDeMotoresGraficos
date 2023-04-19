#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

class 
	Device;

class 
	Texture;

class DeviceContext;

class DepthStencilView;

class 
RenderTargetView {
public: 
	RenderTargetView() = default;
	~RenderTargetView() {};

	//A render-target-view interface identifies the render-target subresources that 
	//can be accessed during rendering.
	//Create the Render Target View, it needs a device & backBuffer
	void
	init(Device device, 
		   Texture backBuffer, 
		   DXGI_FORMAT Format);
	
	void 
	update();
	
	void 
	render(DeviceContext& deviceContext, 
		     DepthStencilView& depthStencilView);
	
	void 
	destroy();

public:
	//A render-target-view interface identifies the render-target subresources that can be accessed during rendering.
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	
};