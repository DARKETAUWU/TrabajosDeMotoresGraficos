#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

class 
	Device;

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
	render();

	void
	destroy();

public:
	ID3D11SamplerState* m_sampler = nullptr;
};