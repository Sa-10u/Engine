#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <list>
#include "Trans.h"
#include"CONSTANT_BUFFER.h"
#include "D3D.h"
#include"M_Quad.h"
#include"LIGHTMANAGER.h"

using namespace std;

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

class LOBJ;

class Fbx
{
public:

	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Trans* transform);
	void    Release();

	void SetLightGroup(LIGHTMANAGER::LightGroup* grp);

	void SetShaderType(SHADER_TYPE type_);

	HRESULT InitVerticies(fbxsdk::FbxMesh* Fmesh);
	HRESULT InitIndexes(fbxsdk::FbxMesh* Fmesh);
	HRESULT InitMaterial(fbxsdk::FbxNode* Fmesh);


	void InitCB();

private:

	int polygon;
	int vertex;
	int material;
	SHADER_TYPE drwtype_;

	ID3D11Buffer* vb;
	ID3D11Buffer** ib;
	ID3D11Buffer* pb;
	ID3D11Buffer* cb;
	MATERIAL* list_material;
	LIGHTMANAGER::LightGroup* lght_;

	int* indcnt_;
};