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
//Tercer Parcial
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ModelLoader.h"
#include "UserInteface.h"
#include "ConstantBuffer.h"


// Global Variables
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
ID3D11Buffer*                       g_Camera = nullptr;


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
//Tercer Parcial
LoadData                            LD;
ShaderProgram                       g_shaderProgram;
VertexBuffer                        g_VertexBuffer;
IndexBuffer                         g_IndexBuffer;
ModelLoader                         g_ModelLoader;
UserInterface                       UI;
ConstantBuffer                      g_ConstantBuffer;

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

    if (FAILED(g_window.init(hInstance, nCmdShow, WndProc, "Ocupo mimir")))
        return 0;

    if( FAILED( InitDevice() ) ){
        destroy();
        return 0;
    }

    //We initialize the time
    g_time.init();

    //We initialize the tranform of our object
    g_transform.init();

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ){
        if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ){
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else{
          //We update the time throughout the execution
           g_time.update();
           update();
           Render();
        }
    }

    destroy();

    return ( int )msg.wParam;
}


HRESULT 
InitDevice(){

    HRESULT hr = S_OK;

    //We command to visualize the screen
    g_swapChain.init(g_device, g_deviceContext, g_backBuffer, g_window);
    //We send the rendering of the screen
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

    g_backBuffer.destroy();
    if (FAILED(hr)) {
      return hr;
    }

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

    //We create the label layout
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

    //We generate the shading of our screen
    g_shaderProgram.init(g_device, "Tutorial07.Fx", Layout);
    //We load our model with the ObjLoader library
    LD = g_ModelLoader.load("Pistol.obj");
    //We load the vertices of the model
    g_VertexBuffer.init(g_device, LD);
    //Load the model indices
    g_IndexBuffer.init(g_device, LD);

    //create the constas buffers
    D3D11_BUFFER_DESC CanBufferDesc;
    memset(&CanBufferDesc, 0, sizeof(CanBufferDesc));
    CanBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    CanBufferDesc.ByteWidth = sizeof(Camera);
    CanBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    CanBufferDesc.CPUAccessFlags = 0;
    hr = g_device.CreateBuffer( &CanBufferDesc, nullptr,  &g_Camera);
    if( FAILED( hr ) )
        return hr;

    //We initialize the frame's cosntantBuffer
    g_ConstantBuffer.init(g_device, sizeof(CBChangesEveryFrame));

    // Load the Texture
    g_ModelTexture.init(g_device, "GunAlbedo.dds");

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
 
    UI.init(g_window.m_hWnd,  g_device.m_device, g_deviceContext.m_deviceContext);
    //g_transform.init();
    
    return S_OK;
}

void 
update() {

    //We call the update class of the ui
    UI.update();
    //We send him to show us the window
    bool show_demo_window = true;
    //We create a variable for the size of the button
    ImVec2 button_size;
    //calculate the size of the screen to be able to create the botton
    ImVec2 width = ImGui::GetWindowSize();
    //We create a variable for the size of the text
    ImVec2 tex_size;
    //We create a variable to which we will assign the value where the center will be positioned
    float center_position_for_button;
    //We create a variable to which we will assign the value where the center will be positioned
    float center_position_for_text;

    //A screen is initialized which will contain the buttons to modify the transform
    ImGui::Begin("TRANSFORM");
    //New Line
    ImGui::NewLine();
    //We initialize the variable of the size
    tex_size = ImVec2{ 150 , 0 };
    //To get the center of the text we need the result of the subtraction of the size of the screen minus the size of the text divided by two
    center_position_for_text = (width.x - tex_size.x) / 2;
    //We give the cursor the result of the previous operation
    ImGui::SetCursorPosX(center_position_for_text);
    //We generate the text with her center
    ImGui::Text("POSITION", tex_size);
    // New line
    ImGui::NewLine();
    //We create a bar with which we will change the x position of the object
    ImGui::SliderFloat("Position X", &g_transform.Posicion3D.x, -4.0f, 2.0f);
    //We create a bar with which we will change the y position of the object
    ImGui::SliderFloat("Position Y", &g_transform.Posicion3D.y, -2.0f, 2.0f);
    //We create a bar with which we will change the z position of the object
    ImGui::SliderFloat("Position Z", &g_transform.Posicion3D.z, -2.0f, 2.0f);
    //new line
    ImGui::NewLine();
    //We initialize the variable of the size
    button_size = ImVec2{ 150 , 0 };
    //To get the center of the button we need the result of the subtraction of the size of the screen minus the size of the button divided by two
    center_position_for_button = (width.x - button_size.x) / 3;
    //We give the cursor the result of the previous operation
    ImGui::SetCursorPosX(center_position_for_button);
    //Send the original values
    if (ImGui::Button("Reset", button_size)) {
      g_transform.Posicion3D.z = 0;
      g_transform.Posicion3D.y = 0;
      g_transform.Posicion3D.x = 0;
    }
    //end of screen
    ImGui::End();

    //A screen is initialized which will contain the buttons to modify the rotation
    ImGui::Begin("ROTATION");
    //New Line
    ImGui::NewLine();
    //We initialize the variable of the size
    tex_size = ImVec2{ 150 , 0 };
    //To get the center of the text we need the result of the subtraction of the size of the screen minus the size of the text divided by two
    center_position_for_text = (width.x - tex_size.x) / 2;
    //We give the cursor the result of the previous operation
    ImGui::SetCursorPosX(center_position_for_text);
    //We generate the text with her center
    ImGui::Text("ROTATION", center_position_for_text);
    //New Line
    ImGui::NewLine();
    //We create a bar with which we will change the x rotationn of the object
    ImGui::SliderFloat("Rotation X", &g_transform.Rotate.x, -6.0f, 6.0f);
    //We create a bar with which we will change the y rotation of the object
    ImGui::SliderFloat("Rotation Y", &g_transform.Rotate.y, -6.0f, 6.0f);
    //We create a bar with which we will change the z rotation of the object
    ImGui::SliderFloat("Rotation Z", &g_transform.Rotate.z, -6.0f, 6.0f);
    //New Line
    ImGui::NewLine();
    //We initialize the variable of the size
    button_size = ImVec2{ 150 , 0 };
    //To get the center of the button we need the result of the subtraction of the size of the screen minus the size of the button divided by two
    center_position_for_button = (width.x - button_size.x) / 3;
    //We give the cursor the result of the previous operation
    ImGui::SetCursorPosX(center_position_for_button);
    //Send the original values
    if (ImGui::Button("Reset", button_size)) {
      g_transform.Rotate.x = 0;
      g_transform.Rotate.y = 0;
      g_transform.Rotate.z = 0;
    }
    //end of screen
    ImGui::End();

    //A screen is initialized which will contain the buttons to modify the color
    ImGui::Begin("COLOR");
    //new line
    ImGui::NewLine();
    //We initialize the variable of the size
    tex_size = ImVec2{ 150 , 0 };
    //To get the center of the text we need the result of the subtraction of the size of the screen minus the size of the text divided by two
    center_position_for_text = width.x - tex_size.x ;
    //We give the cursor the result of the previous operation
    ImGui::SetCursorPosX(center_position_for_text);
    //We generate the text with her center
    ImGui::Text("CUSTOM COLOR", tex_size);
    //new line
    ImGui::NewLine();
    //Color variables are initialized
    static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    //We generate an element where we will modify the colors of the model to our liking
    ImGui::ColorEdit3("color", color);
    // To have the elements within the same line we put an imgui same line
    ImGui::SameLine();
    //Change the color of the model
    g_vMeshColor = color;
    ////We initialize the variable of the size
    button_size = ImVec2{ 109 , 0 };
    //Send the original values
    if (ImGui::Button("Reset", button_size)) {
      color[0] = 1.0f;
      color[1] = 1.0f;
      color[2] = 1.0f;
    }
    //end of screen
    ImGui::End();

    //A screen is initialized which will contain the buttons to modify the color
    ImGui::Begin("INFO");
    //New Line
    ImGui::NewLine();
    //Gives us information about the position of the model
    UI.vec3Control("Position", &g_transform.Posicion3D.x);
    //new line
    ImGui::NewLine();
    //Gives us information about the rotation of the model
    UI.vec3Control("Rotation", &g_transform.Rotate.x);
    //end of screen
    ImGui::End();
  
    //We generate the matrix of the object
    g_World = XMMatrixScaling(.5f, .5f, .5f) * 
              XMMatrixRotationX(g_transform.Rotate.x) * 
              XMMatrixRotationZ(g_transform.Rotate.z) * 
              XMMatrixRotationY(g_transform.Rotate.y) * 
              XMMatrixTranslation(g_transform.Posicion3D.x, 
                                  g_transform.Posicion3D.y, 
                                  g_transform.Posicion3D.z);

    // Update variables that change once per frame
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    g_ConstantBuffer.update(g_deviceContext, 0, nullptr, &cb, 0, 0);

    //UpdateCamera Buffers
    g_deviceContext.UpdateSubresource(g_Camera, 0, nullptr, &cam, 0, 0);
}

void 
destroy(){
    g_deviceContext.destroy();
    g_samplerState.destroy();
    g_ModelTexture.destroy();
    if (g_Camera) g_Camera->Release();
    g_VertexBuffer.destroy();
    g_IndexBuffer.destroy();
    g_shaderProgram.destroy();
    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapChain.destroy();
    UI.render();
    g_device.destroy();;
}


extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT 
CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
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
 
  g_depthStencilView.render(g_deviceContext);
  g_renderTargetView.render(g_deviceContext, g_depthStencilView);
  g_viewport.render(g_deviceContext);
  g_shaderProgram.render(g_deviceContext);
  g_deviceContext.VSSetConstantBuffers(0, 1, &g_Camera);
  g_samplerState.render(g_deviceContext);
  g_VertexBuffer.render(g_deviceContext, 0);
  g_IndexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);
  g_ConstantBuffer.VSSetConstantBuffer(g_deviceContext, 1, 1);
  g_ConstantBuffer.PSSetConstantBuffers(g_deviceContext, 1, 1);
  g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  g_ModelTexture.render(g_deviceContext);
  g_deviceContext.DrawIndexed(LD.index.size(), 0, 0);
  UI.render();
  g_swapChain.present();

    
}


