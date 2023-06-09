#pragma once
#include <d3d11.h>
#include "string"
#include<wrl.h>
using namespace Microsoft::WRL;

class Texture
{
public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();

	ID3D11SamplerState* GetSampler();
	ID3D11ShaderResourceView* GetResourceV();

private:
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
};