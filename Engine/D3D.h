#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum class SHADER_TYPE
{
	SHADER_2D = 0,
	SHADER_3D,
	SHADER_POINT3D,
	SHADER_TOON3D,
	SHADER_CELL3D,
	SHADER_FRENEL3D,

	SHADER_AMMOUNT,
};

namespace D3D
{
	HRESULT Initialize(int winW, int winH, HWND hwnd);

	void BeginDraw();

	void EndDraw();

	void Release();

	void Shader_Initialize2D();
	void Shader_Initialize3D();
	void Shader_InitializePoint3D();
	void Shader_InitializeToon3D();
	void Shader_InitializeCell3D();
	void Shader_InitializeFrenel3D();

	void SetShader(SHADER_TYPE type);
	
	extern ID3D11Device* pDevice_;		//�f�o�C�X
	extern ID3D11DeviceContext* pContext_;

	
}