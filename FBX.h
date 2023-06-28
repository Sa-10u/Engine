#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Trans.h"
#include"CONSTANT_BUFFER.h"
#include "D3D.h"
#include"M_Quad.h"

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

struct MATERIAL
{
	Texture* tex;
	XMFLOAT4 diffuse;
};

class Fbx
{
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Trans* transform, XMFLOAT4 WorldLight);
	void    Release();

	HRESULT InitVerticies(fbxsdk::FbxMesh* Fmesh);
	HRESULT InitIndexes(fbxsdk::FbxMesh* Fmesh);
	HRESULT InitMaterial(fbxsdk::FbxNode* Fmesh);

	void InitCB();

private:

	int polygon;
	int vertex;
	int material;

	ID3D11Buffer* vb;
	ID3D11Buffer** ib;
	ID3D11Buffer* pb;
	ID3D11Buffer* cb;
	MATERIAL* list_material;

	int* indcnt_;
};