#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Trans
{
public:
	XMFLOAT3 pos;	
	XMFLOAT3 rot;	
	XMFLOAT3 size;	

	Trans();

	~Trans();

	void Calc();

	XMMATRIX GetWorldMatrix();
	XMMATRIX GetNormalMatrix();

private:
	XMMATRIX matgra;
	XMMATRIX matrot;
	XMMATRIX matsc;

	XMMATRIX mat;
};

