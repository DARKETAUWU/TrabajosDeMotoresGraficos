#include "DiviceContext.h"



void
DiviceContext::init()
{

}

void 
DiviceContext::render() 
{

}

void 
DiviceContext::update() 
{

}



void 
DiviceContext::destroy() 
{
	m_deviceContext->ClearState();
}

//Vincula uno o mas datos de renderizado automaticamente y
//el bufer de plantilla en cada etapa de prondundidad
void 
DiviceContext::OMSetRenderTargets(	unsigned int NumViews, 
									ID3D11RenderTargetView* const* ppRenderTargetViews, 
									ID3D11DepthStencilView* pDepthStencilView)
{
	m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

//Bind an array of viewports to the rasterizer stage of the pipeline.
void
DiviceContext::RSSetViewports(	unsigned int NumViewports, 
								const D3D11_VIEWPORT* pViewports)
{
	m_deviceContext->RSSetViewports(NumViewports, pViewports);
}

//Bind an input-layout object to the input-assembler stage.
void
DiviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	m_deviceContext->IASetInputLayout(pInputLayout);
}

//Bind an array of vertex buffers to the input-assembler stage.
void 
DiviceContext::IASetVertexBuffers(	unsigned int StartSlot, 
									unsigned int NumBuffers, 
									ID3D11Buffer* const* ppVertexBuffers, 
									const unsigned int* pStrides, 
									const unsigned int* pOffsets)
{
	m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

//Bind an index buffer to the input-assembler stage.
void 
DiviceContext::IASetIndexBuffer(	ID3D11Buffer* pIndexBufferm,
									DXGI_FORMAT Format, 
									unsigned int Offset)
{
	m_deviceContext->IASetIndexBuffer(pIndexBufferm, Format, Offset);
}

//Bind information about the primitive type
//and data order that describes input data for the input assembler stage.
void
DiviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	m_deviceContext->IASetPrimitiveTopology(Topology);
}

//The CPU copies data from memory to a subresource created in non-mappable memory.
void 
DiviceContext::UpdateSubresource(	ID3D11Resource* pDstResource, 
									unsigned int DstSubresource, 
									const D3D11_BOX* pDstBox, 
									const void* pSrcData, 
									unsigned int SrcRowPitch, 
									unsigned int SrcDepthPitch)
{
	m_deviceContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}


//Set all the elements in a render target to one value.
void 
DiviceContext::ClearRenderTargetView(	ID3D11RenderTargetView* pRenderTargetView, 
										const FLOAT ColorRGBA[4])
{
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

//Clears the depth-stencil resource.
void 
DiviceContext::ClearDepthStencilView(	ID3D11DepthStencilView* pDepthStencilView, 
										unsigned int ClearFlags, 
										float Depth, 
										unsigned int Stencil)
{
	m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

//Set a vertex shader to the device.
void 
DiviceContext::VSSetShader(	ID3D11VertexShader* pVertexShader,
							ID3D11ClassInstance* const* ppClassInstances,
							unsigned int NumClassInstances)
{
	m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void
DiviceContext::VSSetConstantBuffers(unsigned int StartSlot, 
									unsigned int NumBuffers, 
									ID3D11Buffer* const* ppConstantBuffers)
{
	m_deviceContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void
DiviceContext::PSSetShader(	ID3D11PixelShader* pPixelShader, 
							ID3D11ClassInstance* const* ppClassInstances, 
							unsigned int NumClassInstances)
{
	m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void 
DiviceContext::PSSetConstantBuffers(unsigned int StartSlot, 
									unsigned int NumBuffers, 
									ID3D11Buffer* const* ppConstantBuffers)
{
	m_deviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void 
DiviceContext::DrawIndexed(	unsigned int IndexCount, 
							unsigned int StartIndexLocation, 
							unsigned int BaseVertexLocation)
{
	m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void 
DiviceContext::PSSetShaderResources(unsigned int StartSlot, 
									unsigned int NumViews, 
									ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void 
DiviceContext::PSSetSamplers(	unsigned int StartSlot,
								unsigned int NumSamplet, 
								ID3D11SamplerState* const* ppSamplers) 
{
	m_deviceContext->PSSetSamplers(StartSlot, NumSamplet, ppSamplers);
}
