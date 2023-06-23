#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Trans.h"

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

class Fbx
{

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Trans& transform);
	void    Release();
};