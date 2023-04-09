#pragma once
//archivo administrador de recursos
//std lib
#include <vector>
#include <iostream>
#include <sstream>

//Windows
#include <windows.h> 

//External Lib
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>


//Internal Includes
#include "resource.h"



#define WINDOWS
#define WARNING( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
//std lib

#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)           \
OutputDebugStringA(_ClassName);                                                          \
OutputDebugStringA(" : In Function : ");                                          \
OutputDebugStringA(_FunctionName);                                                    \
OutputDebugStringA(" : ");                                                                \
OutputDebugStringA(_OutputMessage);                                                    \
OutputDebugStringA("\n");