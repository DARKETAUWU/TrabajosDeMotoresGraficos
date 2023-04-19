//The DepthStencilView library is called
#include "DepthStencilView.h"
//The Device library is called
#include "Device.h"

#include "DeviceContext.h"

//Create a depth stencil view to access the resource data.
void
DepthStencilView::init(Device device,
		       ID3D11Resource* depthStencil,
	               DXGI_FORMAT Format) {
	//In the event that the device is empty, a warning will be shown asking us to check the device
	if (device.m_device == nullptr) {
		WARNING("ERROR: DepthStencilView::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR Device device] \n");
		exit(1);
	}
	//In case the depthStencil is null we will have to check ID3D11Resource* depthStencil
	else if (depthStencil == nullptr) {
		WARNING("ERROR: DepthStencilView::init : [CREATION OF RESOURCE : FALSE] [CHECK FOR ID3D11Resource* depthStencil] \n");
		exit(1);
	}
	else {
		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		memset(&descDSV, 0, sizeof(descDSV));
		descDSV.Format = Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		//Create a depth-stencil view for accessing resource data.
		device.CreateDepthStencilView(depthStencil, &descDSV, &m_pDepthStencilView);
	}
}

void
DepthStencilView::update() {
}

void
DepthStencilView::render(DeviceContext deviceContext) {
	deviceContext.ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//This function releases the pointer ppT and sets it equal to NULL.
void
DepthStencilView::destroy() {
	SAFE_RELEASE(m_pDepthStencilView);
}
