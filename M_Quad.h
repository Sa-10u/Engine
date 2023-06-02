#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"

using namespace DirectX;


class M_Quad
{
public :

	M_Quad();
	~M_Quad();
	HRESULT Initialize();
	void Draw();
	void Release();

private:

	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;

	int VXs;
};

