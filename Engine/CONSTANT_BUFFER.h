#pragma once
#include <DirectXMath.h>
#include <fbxsdk.h>
#include"LOBJ.h"

using namespace DirectX;

class Texture;

struct CONSTANT_BUFFER
{
	XMMATRIX VP_matWLD;
	XMMATRIX matW;
	XMMATRIX matWV;

	XMFLOAT4 matLGT[LIGHT_AMMOUNT];
	XMFLOAT4 matLGTpos[LIGHT_AMMOUNT];

	XMFLOAT4 diffuse;
	int isTex;

	int Type[LIGHT_AMMOUNT];
	float intensity[LIGHT_AMMOUNT];
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

//struct MATERIAL
//{
//	Texture* tex;
//};
struct MATERIAL
{
	Texture* tex;
	XMFLOAT4 diffuse;
};

struct P_LIGHT 
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
	float strength;
};

struct S_LIGHT
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
	float strength;
};
