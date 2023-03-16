#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"

//The Device class is called to be able to occupy its libraries and information
class 
Device;

//Create an input-layout object to describe the input-buffer data for the input-assembler stage.
class
InputLayout{
	public:
		InputLayout() = default;
		~InputLayout() { SAFE_RELEASE(m_inputlayout); };

		//The init class is initialized with the necessary variables to be able to use the input-layout
		void
		init(Device device,
		     std::vector<D3D11_INPUT_ELEMENT_DESC> Layout,
		     ID3DBlob* VertexShaderData);

		void 
		update();

		void 
		render();

		void 
		destroy();

		
	public:
		//An input-layout interface holds a definition of how to feed vertex data that is laid out in memory into the input-assembler stage of the graphics pipeline.
		ID3D11InputLayout* m_inputlayout = nullptr;

};
