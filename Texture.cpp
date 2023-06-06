#include "Texture.h"
#include"D3D.h"
#include<DirectXTex.h>
#include "MACRO.h"

#pragma comment(lib , "DirectXTex.lib")



Texture::Texture()
{
}

Texture::~Texture()
{
	Release();
}

HRESULT Texture::Load(std::string fileName)
{
	using namespace DirectX;

	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());

	TexMetadata metadata_;
	ScratchImage image_;
	HRESULT res;
	res = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE,&metadata_,image_);

	if (FAILED(res))
	{
		return E_FAIL;
	}

	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	D3D::pDevice->CreateSamplerState(&SamDesc, &pSampler_);


	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	res = CreateShaderResourceView(D3D::pDevice, image_.GetImages(), image_.GetImageCount(), metadata_, &pSRV_);
	if (FAILED(res))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Texture::Release()
{
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}
