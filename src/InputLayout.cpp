//The InputLayout library is called, which has several libraries that will be used throughout the project.
#include "InputLayout.h"
//The Device library is called, which has several libraries that will be used throughout the project.
#include "Device.h"

//The init class is initialized with the necessary variables to be able to use the input-layout
void 
InputLayout::init(Device device,
		  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout,
		  ID3DBlob* VertexShaderData){
	if (Layout.size() == 0) {
		WARNING("ERROR: InputLayout::Init : [CREATION OF RESORCE : FALSE] [CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout Size()] \n");
		exit(1);
	}
	else if (VertexShaderData == nullptr) {
		WARNING("EROOR: InputLayout::Init : [CREATION OF RESORCE : FALSE] [CHECK FOR ID3DBlob* VertexShaderData] \n");
		exit(1);
	}

	device.CreateInputLayout(Layout.data(),
				 Layout.size(),
				 VertexShaderData->GetBufferPointer(),
				 VertexShaderData->GetBufferSize(),
				 &m_inputlayout);
}

void 
InputLayout::update() {
}

void 
InputLayout::render(){
}

void 
InputLayout::destroy(){
}

