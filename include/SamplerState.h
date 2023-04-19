#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

//The device class is called to use its variables
class 
Device;

class
	DeviceContext;

class 
SamplerState{
public:
	SamplerState() = default;
	~SamplerState() {};

	// Create the sample state, allow us to modify the dimensions of the texture
	void
	init(Device device);

	void
	update();

	void
	render(DeviceContext& deviceContext);

	void
	destroy();

public:
	//The sampler-state interface holds a description for sampler state that you can bind to any shader stage of the pipeline for reference by texture sample operations.
	ID3D11SamplerState* m_sampler = nullptr;
};