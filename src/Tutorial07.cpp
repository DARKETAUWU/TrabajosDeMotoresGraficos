//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"
//We send to call the commons library which will help us to have several classes with the variables that we need
#include "Commons.h"

#include "CTime.h"


#include "Window.h"
#include "DeviceContext.h"
#include "Device.h"
#include "DepthStencilView.h"
#include "Texture.h"
#include "InputLayout.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "Transform.h"
#include "SamplerState.h"
#include "Viewport.h"

// Global Variables

D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
IDXGISwapChain*                     g_pSwapChain = nullptr;
ID3D11RenderTargetView*             g_pRenderTargetView = nullptr;
ID3D11VertexShader*                 g_pVertexShader = nullptr; 
ID3D11PixelShader*                  g_pPixelShader = nullptr; 

ID3D11Buffer*                       g_pVertexBuffer = nullptr;
ID3D11Buffer*                       g_pIndexBuffer = nullptr;
ID3D11Buffer*                       g_Camera = nullptr;
ID3D11Buffer*                       g_pCBChangesEveryFrame = nullptr;
ID3D11SamplerState*                 g_pSamplerLinear = nullptr;

XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

//Se asigna la variable cam que mandara llamar a los datos de la funcion Camera
Camera cam; 
//We initialize the variant of the speed with which it will move
float fSpeed = 0.1f; 
//To use the variables we need to call the Time library, but first we must have a variable
CTime                               g_time; 
Window                              g_window;
DeviceContext                       g_deviceContext;
Device                              g_device;
DepthStencilView                    g_depthStencilView;
Texture                             g_ModelTexture;
Texture                             g_depthStencil;
Texture                             g_backBuffer;
InputLayout                         g_InputLayout;
SwapChain                           g_swapChain;
RenderTargetView                    g_renderTargetView;
SamplerState                        g_samplerState;
Viewport                            g_viewport;
Transform                           g_transform;

HRESULT 
InitWindow( HINSTANCE hInstance, 
            int nCmdShow ); 

HRESULT 
InitDevice(); 
LRESULT 
CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void 
Render();
void 
update();
void 
destroy();

int 
WINAPI wWinMain( HINSTANCE hInstance, 
                 HINSTANCE hPrevInstance, 
                 LPWSTR lpCmdLine, 
                 int nCmdShow ){
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

   

    if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
        return 0;


    if( FAILED( InitDevice() ) ){
        //CleanupDevice();
        destroy();
        return 0;
    }

    g_time.init();

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ){
        if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ){
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else{
           g_time.update();
           update();
           Render();
            
        }
    }

   
    destroy();

    return ( int )msg.wParam;
}


HRESULT 
CompileShaderFromFile(  char* szFileName, 
                        LPCSTR szEntryPoint, 
                        LPCSTR szShaderModel, 
                        ID3DBlob** ppBlobOut ){
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, 
                                nullptr, 
                                nullptr, 
                                szEntryPoint, 
                                szShaderModel, 
                                dwShaderFlags, 
                                0, 
                                nullptr, 
                                ppBlobOut, 
                                &pErrorBlob, 
                                nullptr);
    if (FAILED(hr)) {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}


HRESULT 
InitDevice(){
    HRESULT hr = S_OK;

    g_swapChain.init(g_device, g_deviceContext, g_backBuffer, g_window);
 
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

    g_backBuffer.destroy();
    if (FAILED(hr))
        return hr;

    // Create depth stencil texture
    g_depthStencil.init( g_device,
                         g_window.m_width,
                         g_window.m_height,
                         DXGI_FORMAT_D24_UNORM_S8_UINT,
                         D3D11_BIND_DEPTH_STENCIL);

    // Create the depth stencil view
    g_depthStencilView.init(g_device, 
                            g_depthStencil.m_texture, 
                            DXGI_FORMAT_D24_UNORM_S8_UINT);

    // Setup the viewport
    g_viewport.init(g_window);

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile( "Tutorial07.fx", "VS", "vs_4_0", &pVSBlob );
    if( FAILED( hr ) ){
        MessageBox( nullptr,
                    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
        return hr;
    }

    hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    if (FAILED(hr)){
        pVSBlob->Release(); 
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] = { { 
            "POSITION",                   //Semantic Name  -> Identificador para la estructura en el shader
            0,                              //Semantic Index -> En caso de tener mas de un Semantic Name igual
            DXGI_FORMAT_R32G32B32_FLOAT,    //Format         -> Clasificador para el tipo de datos
            0,                              //Input Slot     -> Revisa si existe mas de un vertex buffer (Esto es importante a considerar cuadno existan mas modelos)
            D3D11_APPEND_ALIGNED_ELEMENT,   //AlignedByOffset  -> Administra el espacio en memoria y su ajuste idoneo
            D3D11_INPUT_PER_VERTEX_DATA,    //InputSlotClassAt -> Se configura que tipo de dato se está asignando
            0                               //InstanceDataRate -> Actualización de datos
        },{ 
            "TEXCOORD", 
             0, 
             DXGI_FORMAT_R32G32_FLOAT, 
             0,
             D3D11_APPEND_ALIGNED_ELEMENT, 
             D3D11_INPUT_PER_VERTEX_DATA, 
             0 
},
    };
    unsigned int numElements = ARRAYSIZE(layout);

    std::vector <D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

   

    // Create the input layout
    g_InputLayout.init(g_device, Layout, pVSBlob);
   
    pVSBlob->Release();
    if( FAILED( hr ) )
        return hr;

   

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile( "Tutorial07.fx", "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) ){
        MessageBox( nullptr,
                    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
        return hr;
    }

    // Create the pixel shader
    hr = g_device.CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader );
    pPSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

    D3D11_BUFFER_DESC bd;
    memset( &bd, 0, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    memset( &InitData, 0, sizeof(InitData) );
    InitData.pSysMem = vertices;
    hr = g_device.CreateBuffer( &bd, 
                                &InitData, 
                                &g_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
    g_deviceContext.IASetVertexBuffers( 0, 
                                        1, 
                                        &g_pVertexBuffer, 
                                        &stride, 
                                        &offset );


    WORD indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( WORD ) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices;
    hr = g_device.CreateBuffer( &bd, 
                                &InitData, 
                                &g_pIndexBuffer );
    if( FAILED( hr ) )
        return hr;

    // Set index buffer
    g_deviceContext.IASetIndexBuffer(   g_pIndexBuffer, 
                                        DXGI_FORMAT_R16_UINT, 
                                        0 );

    // Set primitive topology
    g_deviceContext.IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Camera);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = g_device.CreateBuffer(&bd, nullptr, &g_Camera);
    if (FAILED(hr))
        return hr;

    bd.ByteWidth = sizeof(Camera);
    hr = g_device.CreateBuffer(&bd, nullptr, &g_Camera);
    if (FAILED(hr))
        return hr;
    
    bd.ByteWidth = sizeof(CBChangesEveryFrame);
    hr = g_device.CreateBuffer( &bd, nullptr, &g_pCBChangesEveryFrame );
    if( FAILED( hr ) )
        return hr;

    // Load the Texture
    g_ModelTexture.init(g_device, "seafloor.dds");
    //hr = D3DX11CreateShaderResourceViewFromFile(g_device., "seafloor.dds", nullptr, nullptr, &g_pTextureRV, nullptr );
    if( FAILED( hr ) )
        return hr;

    // Create the sample state
    g_samplerState.init(g_device);

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f );

    cam.mView = XMMatrixTranspose(g_View);
    cam.mProjection = XMMatrixTranspose(g_Projection);
 
    
    return S_OK;
}


void 
update(){

    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE){
        g_time.m_deltatime += (float)XM_PI * 0.0125f;
    }
    else{
        static unsigned int dwTimeStart = 0;
        unsigned int dwTimeCur = GetTickCount();
        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;
        g_time.m_deltatime = (dwTimeCur - dwTimeStart) / 1000.0f;
    }
    g_transform.m_ScaleNum += 0.0002f;
    

    g_World = XMMatrixScaling(.5f, .5f, .5f) * XMMatrixRotationY(g_time.m_deltatime) * XMMatrixTranslation(g_transform.Posicion3D.x, g_transform.Posicion3D.y, g_transform.Posicion3D.z);

    // Update variables that change once per frame
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;

    //UpdateCamera Buffers
    g_deviceContext.UpdateSubresource(g_Camera, 0, nullptr, &cam, 0, 0);

    //Update Mesh Buffers
    g_deviceContext.UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

}

void 
destroy(){
    g_deviceContext.destroy();
    g_samplerState.destroy();
    g_ModelTexture.destroy();

    if (g_Camera) g_Camera->Release();
    if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
    if (g_pVertexBuffer) g_pVertexBuffer->Release();
    if (g_pIndexBuffer) g_pIndexBuffer->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (g_pPixelShader) g_pPixelShader->Release();

    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapChain.destroy();
    g_device.destroy();;
}

LRESULT 
CALLBACK WndProc(HWND hWnd, 
                 UINT message, 
                 WPARAM wParam, 
                 LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        case WM_KEYDOWN:
            //To use the movement system we based ourselves on the way in which unity handles the movement. 
            //Therefore, in the system we put that in case the program receives an instruction through the keyboard, it will make a movement

            switch (wParam)
            {
                //For the movement to the left we use the A key, so in the event that the keyboard marks that key
                case 'A': 
                    // For movement to the left, its vector should be decreased by multiplying the velocity by the real time.
                    g_transform.Posicion3D.x -= fSpeed * g_time.m_deltatime;
                    break;
                //For the movement to the right we use the D key, so in the event that the keyboard marks that key
                case 'D': 
                    // it will move the object along the x axis, multiplying its speed by the real time of the computer
                    g_transform.Posicion3D.x += fSpeed * g_time.m_deltatime;
                    break;
                //For the upward movement we use the D key, so in the event that the keyboard marks that key
                case 'W':
                    //For the upward movement, the speed must be added to the vector "y" multiplied by the real time
                    g_transform.Posicion3D.y += fSpeed * g_time.m_deltatime;
                    break;
                //For downward movement, the keyboard must detect that the letter "S" is pressed.
                case 'S':  
                    //For its movement, the vector "y" will be decreased by multiplying its speed with real time
                    g_transform.Posicion3D.y -= fSpeed * g_time.m_deltatime;
                    break;
                // Forward movement, to detect forward movement, the system should detect the "Q" key
                case 'Q': 
                    // For its movement the vector will be increased in "z" multiplying the speed by the real time
                    g_transform.Posicion3D.z += fSpeed * g_time.m_deltatime;
                    break;
                // For the movement towards the bottom the case must detect the pressure of the "E" key
                case 'E': 
                    // To move it, you have to decrease in its vector z the result of multiplying the velocity by the time.
                    g_transform.Posicion3D.z -= fSpeed * g_time.m_deltatime;
                    break;
                //When it detects that the keyboard presses the G key, it resets its position to 0 in all directions.
                case 'G': 
                    g_transform.Posicion3D.x = 0;
                    g_transform.Posicion3D.y = 0;
                    g_transform.Posicion3D.z = 0;
                    break;
                    //The 0 button changes its color
                case '0':
                    g_vMeshColor = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
                    break;
                    //The 1 button changes its color
                case '1':
                    g_vMeshColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
                    break;
                    //The 2 button changes its color
                case '2':
                    g_vMeshColor = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
                    break;
                    //The 3 button changes its color
                case '3':
                    g_vMeshColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
                    break;
            }

            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void 
Render()
{
 
    
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 

    //Set all the elements in a render target to one value.
    g_deviceContext.ClearRenderTargetView(g_renderTargetView.m_renderTargetView, ClearColor);
    //Clears the depth-stencil resource.
    g_deviceContext.ClearDepthStencilView(g_depthStencilView.m_pDepthStencilView,D3D11_CLEAR_DEPTH, 1.0f, 0);
    //Bind one or more render targets atomically and the depth-stencil buffer to the output-merger stage.
    g_deviceContext.OMSetRenderTargets(1, &g_renderTargetView.m_renderTargetView, g_depthStencilView.m_pDepthStencilView);
    //Bind an array of viewports to the rasterizer stage of the pipeline.
    g_deviceContext.RSSetViewports(1, &g_viewport.m_viewport);
    // Set the input layout
    g_deviceContext.IASetInputLayout(g_InputLayout.m_inputlayout);
    //Set a vertex shader to the device.
    g_deviceContext.VSSetShader(g_pVertexShader, nullptr, 0);
    //Sets the constant buffers used by the vertex shader pipeline stage.
    g_deviceContext.VSSetConstantBuffers(0, 1, &g_Camera);
    //Sets the constant buffers used by the vertex shader pipeline stage.
    g_deviceContext.VSSetConstantBuffers(1, 1, &g_pCBChangesEveryFrame);
    //Sets a pixel shader to the device.
    g_deviceContext.PSSetShader(g_pPixelShader, nullptr, 0);
    //Sets the constant buffers used by the pixel shader pipeline stage.
    g_deviceContext.PSSetConstantBuffers(1, 1, &g_pCBChangesEveryFrame);
    //Bind an array of shader resources to the pixel shader stage.
    g_deviceContext.PSSetShaderResources(0, 1, &g_ModelTexture.m_textureFromImg);
    //Set an array of sampler states to the pixel shader pipeline stage.
    g_deviceContext.PSSetSamplers(0, 1, &g_samplerState.m_sampler);
    //Draw indexed, non-instanced primitives.
    g_deviceContext.DrawIndexed(36, 0, 0);
    // Present our back buffer to our front buffer
    g_swapChain.present();
}


