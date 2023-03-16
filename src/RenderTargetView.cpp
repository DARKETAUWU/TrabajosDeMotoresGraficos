//The RenderTargetView library is called, which has several libraries that will be used throughout the project.
#include "RenderTargetView.h"
//The Device library is called, which has several libraries that will be used throughout the project.
#include "Device.h"
//The Texture library is called, which has several libraries that will be used throughout the project.
#include "Texture.h"

//A render-target-view interface identifies the render-target subresources that 
	//can be accessed during rendering.
	//Create the Render Target View, it needs a device & backBuffer
void 
RenderTargetView::init(Device device, 
		       Texture backBuffer, 
		       DXGI_FORMAT Format){
	if (device.m_device == nullptr) {
		WARNING("ERROR: RenderTargetView::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Device device] \n");
		exit(1);
	}
	else if (backBuffer.m_texture == nullptr) {
		WARNING("ERROR: RenderTargetView::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Texture backBuffer] \n");
		exit(1);
	}

	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);
}

void 
RenderTargetView::update(){
}


void 
RenderTargetView::render(){
}

void 
RenderTargetView::destroy(){
	SAFE_RELEASE(m_renderTargetView);
}
