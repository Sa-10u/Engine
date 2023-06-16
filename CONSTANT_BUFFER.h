#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX VP_matWLD;
	XMMATRIX matW;

	XMFLOAT4 matLGT;
};
struct CONSTANT_BUFFER_SPRITE
{
	XMMATRIX matW;
};

struct VERTEX
{
	XMVECTOR pos;
	XMVECTOR uv;
	XMVECTOR normal;

};
struct VERTEX_SPRITE
{
	XMVECTOR pos;
	XMVECTOR uv;
};
