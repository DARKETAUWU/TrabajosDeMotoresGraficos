#pragma once
//archivo administrador de recursos
#include <windows.h> 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#include <vector>
#include <string.h>
#include "Time.h"
#define WINDOWS
#define DBOUT( s )            \
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