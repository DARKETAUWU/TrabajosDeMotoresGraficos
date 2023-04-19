#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"
//The Commons library is called, which has several libraries that will be used throughout the project.
#include "Commons.h"

//The Device class is called to use its variables
class
Device;

class
	DeviceContext;

class
Texture{
public:
	Texture() = default;
	~Texture();

	//Load all texture processes
	void
	init(Device device, std::string textureName);

	//Load the texture with the divice variable, if height and width, the format it occupies
	void
	init(Device device,
	     unsigned int width,
	     unsigned int height,
	     DXGI_FORMAT Format,
	     unsigned int BindFlags);

	void
	update();

	void
	render(DeviceContext& deviceContext);

	void
	destroy();


public:
	//This variable is in charge if handle a texture resource as data
	ID3D11Texture2D* m_texture = nullptr;

	//This variable is in charge of hanlde a texture resource as image data
	ID3D11ShaderResourceView* m_textureFromImg = nullptr;

};
