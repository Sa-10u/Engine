#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX VP_matWLD;
	XMMATRIX matW;
};

struct VERTEX
{
	XMVECTOR pos;
	XMVECTOR uv;
	XMVECTOR normal;

};
