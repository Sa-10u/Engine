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

public:
	Sprite();
	~Sprite();
	HRESULT Initialize(VERTEX vcs[], int vcw, string pic, int index[], int inds);
	virtual HRESULT Initialize(void);
	void Draw(XMMATRIX* worldMatrix, XMFLOAT4* wldLGT);
	void Release();

protected:

	UINT64 VCs;
	ID3D11Buffer* pVXBuffer_;
	ID3D11Buffer* pIndBuffer_;
	ID3D11Buffer* pConstBuffer_;
	Texture* pTex_;

private:

	virtual void Vertex_Initialize();
	HRESULT CreateVertexBuffer();
	virtual void IndexData_Initialize();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	void PassDataToCB(DirectX::XMMATRIX& wldmat);
	void SetBufferToPipeline();
};

