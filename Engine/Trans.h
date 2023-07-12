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

	XMMATRIX GetRotationMatrix();
	XMMATRIX GetMigrationMatrix();
	XMMATRIX GetScalingMatrix();

	Trans* parent_;

private:
	XMMATRIX matgra;
	XMMATRIX matrot;
	XMMATRIX matsc;

	XMMATRIX mat;

};

