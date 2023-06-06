#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"

using namespace DirectX;


class M_Quad
{
public :

	M_Quad();
	~M_Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX* worldMatrix);
	void Release();

private:

	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;

	int VXs;
};

