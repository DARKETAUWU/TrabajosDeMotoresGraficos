#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

//The Device class is called to use its variables
class
Device;

class
DeviceContext;

class
DepthStencilView{
public:
	DepthStencilView() = default;
	~DepthStencilView() { SAFE_RELEASE(m_pDepthStencilView) };

	// Create the depth stencil view
	void
	init(Device device, 
		   ID3D11Resource* depthStencil, 
		   DXGI_FORMAT Format);

	void
	update();

	void
	render(DeviceContext& deviceContex);

	void
	destroy();

public:
	//A depth-stencil-view interface accesses a texture resource during depth-stencil testing
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

};