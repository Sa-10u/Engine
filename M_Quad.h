#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"
#include "Texture.h"
#include<string>
#include "CONSTANT_BUFFER.h"
#include "Trans.h"

using namespace DirectX;
using std::string;


class M_Quad
{
public :

	M_Quad();
	~M_Quad();
	HRESULT Initialize(VERTEX vcs[], int vcw ,string pic , int index[] , int inds);
	virtual HRESULT Initialize(void);
	void Draw(Trans* trans , XMFLOAT4* wldLGT , XMFLOAT4 LightPos);
	void Draw(XMMATRIX* trans, XMFLOAT4* wldLGT , XMFLOAT4 LightPos);
	void Release();

private:

	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;
	Texture* pTex_;
	//Trans trans;

	int VCs;
};

