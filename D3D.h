#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace D3D
{
	void Initialize(int winW, int winH, HWND hwnd);

	void BeginDraw();

	void EndDraw();

	void Release();

	void Shader_Initialize();

	
	extern ID3D11Device* pDevice;		//デバイス
	
}