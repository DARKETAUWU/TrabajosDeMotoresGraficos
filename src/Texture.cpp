//The Texture library is called, which has several libraries that will be used throughout the project.
#include "Texture.h"
//The Device library is called, which has several libraries that will be used throughout the project.
#include "Device.h"



void
Texture::destroy() {
	if (m_texture != nullptr) {
		SAFE_RELEASE(m_texture);
	}
	else if (m_textureFromImg != nullptr) {
		SAFE_RELEASE(m_textureFromImg);
	}
}

Texture::~Texture(){
}

//Load all texture processes
void
Texture::init(Device device, std::string textureName) {

	//If the dive is empty, our system will send a warning explaining what resource is missing
	if (device.m_device == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Device device] \n");
		exit(1);
	}

	//Check if texture exist

	HRESULT hr = S_OK;

	//Create a shader-resource view from a file.
	hr = D3DX11CreateShaderResourceViewFromFile(device.m_device,
		                                    textureName.c_str(),
		                                    nullptr,
		                                    nullptr,
		                                    &m_textureFromImg,
		                                    nullptr);
	//In case of failure, the hr will show us that the creation of the resource is false and we must check the correct name of the texture
	if (FAILED(hr)) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR correct texture name in Filepath] \n");
		exit(1);
	}
}

//Load the texture with the divice variable, if height and width, the format it occupies
void
Texture::init(	Device device,
	        unsigned int width,
                unsigned int height,
	        DXGI_FORMAT Format,
	        unsigned int BindFlags) {
	//In case of failure, it will show us the message to check the device
	if (device.m_device == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Device device] \n");
		exit(1);
	}

	//If the height is equal to 0 or the width is equal to 0, a warning will be shown which we must check this data
	if (width <= 0 || height <= 0) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Width or Height] \n");
		exit(1);
	}

	HRESULT hr = S_OK;

	//Describe la estructura de una textura
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = width;		// width;
	desc.Height = height;	// height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = Format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = BindFlags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	//Identifies how to bind a resource to the pipeline.
	if (BindFlags == D3D11_BIND_DEPTH_STENCIL) {
		hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
	}

	//In case of having an empty texture, a warning will be shown to check said data.
	if (m_texture == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR m_texture] \n");
		exit(1);
	}
	//If the hr fails, a warning is issued about checking the texture creation
	else if (FAILED(hr)) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR CreateTexture2D] \n");
		exit(1);
	}

}

void Texture::update(){
}

void Texture::render(){
}
