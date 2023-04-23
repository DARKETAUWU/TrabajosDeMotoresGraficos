#include "IndexBuffer.h"
#include "Device.h"
#include "DeviceContext.h"

void 
IndexBuffer::init(Device device, 
                  LoadData loadData){
  if (device.m_device == nullptr) {
    WARNING("ERROR: IndexBuffer::init : [CREATION OF RESORCE : FALSE] [CHECK FOR Device device]");
    exit(1);
  }
  else if(loadData.index.size() == 0) {
    WARNING("ERROR: IndexBuffer::init : [CREATION OF RESORCE : FALSE] [CHECK FOR LoadData loadData.index.size()]");
    exit(1);
  }
  else if (loadData.numIndex == 0) {
    WARNING("ERROR: IndexBuffer::init : [CREATION OF RESORCE : FALSE] [CHECK FOR LoadData loadData.numIndex]");
    exit(1);
  }

  HRESULT hr = S_OK;
  D3D11_BUFFER_DESC indexBufferDesc;
  memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned int) * loadData.numIndex;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA InitData;
  InitData.pSysMem = loadData.index.data();

  hr = device.CreateBuffer(&indexBufferDesc, &InitData, &m_indexBuffer);

  if (FAILED(hr)) {
    WARNING("ERROR: IndexBuffer::init : [CREATION OF RESORCE : FALSE] [CHECK FOR CreateBuffer]");
    exit(1);
  }

}

void 
IndexBuffer::update()
{
}

void 
IndexBuffer::render(DeviceContext& deviceContex, 
                    unsigned int StartSlot)
{
  deviceContex.IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void 
IndexBuffer::destroy()
{
  SAFE_RELEASE(m_indexBuffer);
}
