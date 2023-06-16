#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

HRESULT Sprite::Initialize(VERTEX vcs[], int vcw, string pic, int index[], int inds)
{
	return E_NOTIMPL;
	
}

HRESULT Sprite::Initialize(void)
{
	return E_NOTIMPL;
}

void Sprite::Draw(XMMATRIX* worldMatrix, XMFLOAT4* wldLGT)
{
}

void Sprite::Release()
{
}

void Sprite::Vertex_Initialize()
{
}

HRESULT Sprite::CreateVertexBuffer()
{
	return E_NOTIMPL;
}

void Sprite::IndexData_Initialize()
{
}

HRESULT Sprite::CreateConstantBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::LoadTexture()
{
	return E_NOTIMPL;
}

void Sprite::PassDataToCB(DirectX::XMMATRIX& wldmat)
{
}

void Sprite::SetBufferToPipeline()
{
}
