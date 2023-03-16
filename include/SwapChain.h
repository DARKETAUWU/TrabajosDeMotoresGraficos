#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

//The device class is called to use its variables
class
Device;

//The DeviceContext class is called to use its variables
class
DeviceContext;

//The Window class is called to use its variables
class
Window;

//The Texture class is called to use its variables
class
Texture;

//A swap chain is a collection of buffers that are used for displaying frames
class 
SwapChain {

public:
	SwapChain() = default;
	~SwapChain() {};

	// Create Direct3D device
	void
	init(Device& device,
	     DeviceContext& deviceContext,
	     Texture& backBuffer,
	     Window window);

	void
	update();

	void
	render();

	void
	destroy();

	//Present, that we present in the screen
	void
	present();


private:
	//A NULL driver, which is a reference driver without render capability.
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
	//Describes the set of features targeted by a Direct3D device.
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	//An IDXGISwapChain interface implements one or more surfaces for storing rendered data before presenting it to an output.
	IDXGISwapChain* m_swapChain = nullptr;

};
