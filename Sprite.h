#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"
#include "Texture.h"
#include <string>
#include "CONSTANT_BUFFER.h"

using std::string;


class Sprite
{
	Sprite();
	~Sprite();
	HRESULT Initialize(VERTEX vcs[], int vcw, string pic, int index[], int inds);
	virtual HRESULT Initialize(void);
	void Draw(XMMATRIX* worldMatrix, XMFLOAT4* wldLGT);
	void Release();

private:

	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;
	Texture* pTex_;

	int VCs;
};

