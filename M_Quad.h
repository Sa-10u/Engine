#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"
#include "Texture.h"
#include<string>

using namespace DirectX;
using std::string;


class M_Quad
{
public :

	M_Quad();
	~M_Quad();
	HRESULT Initialize(VERTEX vcs[], string pic , int index[]);
	HRESULT Initialize();
	void Draw(XMMATRIX* worldMatrix);
	void Release();

private:

	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;
	Texture* pTex_;

	int VCs;
};

