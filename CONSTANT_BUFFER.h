#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX VP_matWLD;
};

struct VERTEX
{
	XMVECTOR pos;
	XMVECTOR uv;


};
