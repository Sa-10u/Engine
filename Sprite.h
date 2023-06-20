#pragma once
#include "D3D.h"
#include <DirectXMath.h>
#include "MACRO.h"
#include "CAM.h"
#include "Texture.h"
#include <string>
#include "CONSTANT_BUFFER.h"
#include"Trans.h"

using std::string;

class Sprite
{

public:
	Sprite();
	~Sprite();
	HRESULT Initialize(VERTEX vcs[], int vcw, string pic, int index[], int inds);
	virtual HRESULT Initialize(UINT const winH, UINT const winW);
	void Draw(Trans* worldMatrix);
	void Draw(XMMATRIX* worldMatrix);
	void Release();

protected:

	UINT64 VCs;
	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;
	Texture* pTex_;

};

