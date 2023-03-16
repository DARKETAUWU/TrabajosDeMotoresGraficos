//The DepthStencilView library is called
#include "DeviceContext.h"

void
DeviceContext::init() {
}

void
DeviceContext::update() {
}

void
DeviceContext::render() {
}

//The entire device context is cleaned
void
DeviceContext::destroy() {
	m_deviceContext->ClearState();
}

//The DrawIndexed function draws indexed primitives.
void
DeviceContext::DrawIndexed(unsigned int IndexCount,
	unsigned int StartIndexLocation,
	unsigned int BaseVertexLocation) {
	m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

//Set an array of sampler states to the pixel shader pipeline stage.
void
DeviceContext::PSSetSamplers(unsigned int StartSlot,
	unsigned int NumSamplers,
	ID3D11SamplerState* const* ppSamplers) {
	m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

//Bind an array of shader resources to the pixel shader stage.
void
DeviceContext::PSSetShaderResources(unsigned int StartSlot,
	unsigned int NumViews,
	ID3D11ShaderResourceView* const* ppShaderResourceViews) {
	m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

//Sets the constant buffers used by the pixel shader pipeline stage
void
DeviceContext::PSSetConstantBuffers(	unsigned int StartSlot,
										unsigned int NumBuffers,
										ID3D11Buffer* const* ppConstantBuffers) {
	m_deviceContext->PSSetConstantBuffers(	StartSlot, 
											NumBuffers, 
											ppConstantBuffers);
}

//Sets a pixel shader to the device.
void
DeviceContext::PSSetShader(	ID3D11PixelShader* pPixelShader,
							ID3D11ClassInstance* const* ppClassInstances,
							unsigned int NumClassInstances){
	m_deviceContext->PSSetShader(	pPixelShader, 
									ppClassInstances, 
									NumClassInstances);
}

//Sets the constant buffers used by the vertex shader pipeline stage.
void
DeviceContext::VSSetConstantBuffers(unsigned int StartSlot,
									unsigned int NumBuffers,
									ID3D11Buffer* const* ppConstantBuffers){
	m_deviceContext->VSSetConstantBuffers(	StartSlot, 
											NumBuffers, 
											ppConstantBuffers);
}

void
DeviceContext::VSSetShader(	ID3D11VertexShader* pVertexShader,
							ID3D11ClassInstance* const* ppClassInstances,
							unsigned int NumClassInstances) {
	m_deviceContext->VSSetShader(pVertexShader, 
								ppClassInstances, 
							    NumClassInstances);
}

//Set a vertex shader to the device.
void
DeviceContext::ClearDepthStencilView(	ID3D11DepthStencilView* pDepthStencilView,
										unsigned int ClearFlags,
										float Depth,
										unsigned int Stencil) {
	m_deviceContext->ClearDepthStencilView(	pDepthStencilView, 
											ClearFlags, 
											Depth, 
											Stencil);
}

//Set all the elements in a render target to one value.
void
DeviceContext::ClearRenderTargetView(	ID3D11RenderTargetView* pRenderTargetView,
										const float ColorRGBA[4]) {
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

//Bind one or more render targets atomically and the depth-stencil buffer to the output-merger stage.
void
DeviceContext::OMSetRenderTargets(		unsigned int NumViews,
										ID3D11RenderTargetView* const* ppRenderTargetViews,
										ID3D11DepthStencilView* pDepthStencilView) 
{

	m_deviceContext->OMSetRenderTargets(NumViews, 
										ppRenderTargetViews, 
										pDepthStencilView);
}

//Bind an array of viewports to the rasterizer stage of the pipeline.
void
DeviceContext::RSSetViewports(	unsigned int NumViewports,
								const D3D11_VIEWPORT* pViewports) 
{
	m_deviceContext->RSSetViewports(NumViewports, 
									pViewports);
}

//Bind an input-layout object to the input-assembler stage.
void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) 
{
	m_deviceContext->IASetInputLayout(pInputLayout);
}

//Bind an array of vertex buffers to the input-assembler stage.
void
DeviceContext::IASetVertexBuffers(	unsigned int StartSlot,
									unsigned int NumBuffers,
									ID3D11Buffer* const* ppVertexBuffers,
									const unsigned int* pStrides,
									const unsigned int* pOffsets) 
{
	m_deviceContext->IASetVertexBuffers(StartSlot,
										NumBuffers,
										ppVertexBuffers,
										pStrides,
										pOffsets);
}

//Bind an index buffer to the input-assembler stage.
void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
								DXGI_FORMAT Format,
								unsigned int Offset) 
{
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

//Bind information about the primitive type, and data order that describes input data for the input assembler stage.
void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) 
{
	m_deviceContext->IASetPrimitiveTopology(Topology);
}

//The CPU copies data from memory to a subresource created in non-mappable memory.
void
DeviceContext::UpdateSubresource(	ID3D11Resource* pDstResource,
									unsigned int DstSubresource,
									const D3D11_BOX* pDstBox,
									const void* pSrcData,
									unsigned int SrcRowPitch,
									unsigned int SrcDepthPitch) 
{
	
		m_deviceContext->UpdateSubresource(	pDstResource,
											DstSubresource,
											pDstBox,
											pSrcData,
											SrcRowPitch,
											SrcDepthPitch);
}