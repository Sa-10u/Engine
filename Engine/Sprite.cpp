#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

HRESULT Sprite::Initialize(VERTEX vcs[], int vcw, string pic, int index[], int inds)
{
	HRESULT hr = E_FAIL;

	{
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = vcw;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = vcs;
		hr = D3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVXBuffer_);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Buffer_Discription has been Mistook", "ERROR", MB_OK);
			return hr;
		}
	}

	{

		VCs = inds;

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = VCs;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		hr = D3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndBuffer_);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Buffer_Description has been Mistook", "ERROR", MB_OK);

			return hr;
		}
	}

	{
		D3D11_BUFFER_DESC cb;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_SPRITE);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		hr = D3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstBuffer_);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Constant_Buffer has been Mistook", "ERROR", MB_OK);

			return hr;
		}
	}

	pTex_ = new Texture();
	hr = pTex_->Load(pic);

	if (FAILED(hr))return hr;

	return S_OK;
}

HRESULT Sprite::Initialize(UINT const winH, UINT const winW)
{
	VERTEX vx[] =
	{
		{XMVectorSet((10*2 - winW*1.0)/winW  ,(0 *-2 - winH * -1.0) / winH  ,0.0f,0.0f) ,XMVectorSet(0,0,0,0)},
		{XMVectorSet((100*2.0 - winW*1.0) / winW , (0 *-2.0- winH * -1.0) / winH , 0.0f, 0.0f),XMVectorSet(1,0,0,0)},
		{XMVectorSet((100*2.0 - winW*1.0) / winW , (80 *-2.0- winH * -1.0) / winH , 0.0f , 0.0f),XMVectorSet(1,1,0,0)},
		{XMVectorSet((10*2.0 - winW*1.0) / winW, (80*-2.0  - winH * -1.0) / winH , 0.0f, 0.0f),XMVectorSet(0,1,0,0)},
	};

	//float tes = (winH * -2.0 - winH * -1.0) / winH;

	int Ind[] = { 0,1,2 , 0,2,3 };

	HRESULT res;

	res = this->Initialize(ARRAY_WITH_SIZE(vx), "Assets/dice.png", ARRAY_WITH_SIZE(Ind));

	return res;
}

void Sprite::Draw(Trans* wldMat)
{
	D3D::SetShader(SHADER_TYPE::SHADER_2D);

	CONSTANT_BUFFER_SPRITE cb;
	cb.matW = XMMatrixTranspose(wldMat->GetWorldMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	D3D::pContext_->Map(pConstBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	D3D::pContext_->Unmap(pConstBuffer_, 0);	//再開

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	D3D::pContext_->IASetVertexBuffers(0, 1, &pVXBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	D3D::pContext_->IASetIndexBuffer(pIndBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	D3D::pContext_->VSSetConstantBuffers(0, 1, &pConstBuffer_);	//頂点シェーダー用	
	D3D::pContext_->PSSetConstantBuffers(0, 1, &pConstBuffer_);

	ID3D11SamplerState* pSampler = pTex_->GetSampler();

	D3D::pContext_->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = pTex_->GetResourceV();

	D3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	D3D::pContext_->DrawIndexed(VCs, 0, 0);
}

void Sprite::Draw(XMMATRIX* worldMatrix)
{
	D3D::SetShader(SHADER_TYPE::SHADER_2D);

	CONSTANT_BUFFER_SPRITE cb;
	cb.matW = XMMatrixTranspose(*worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	D3D::pContext_->Map(pConstBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	D3D::pContext_->Unmap(pConstBuffer_, 0);	//再開

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	D3D::pContext_->IASetVertexBuffers(0, 1, &pVXBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	D3D::pContext_->IASetIndexBuffer(pIndBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	D3D::pContext_->VSSetConstantBuffers(0, 1, &pConstBuffer_);	//頂点シェーダー用	
	D3D::pContext_->PSSetConstantBuffers(0, 1, &pConstBuffer_);

	ID3D11SamplerState* pSampler = pTex_->GetSampler();

	D3D::pContext_->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = pTex_->GetResourceV();

	D3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	D3D::pContext_->DrawIndexed(VCs, 0, 0);
}

void Sprite::Release()
{
	SAFE_RELEASE(pVXBuffer_);
	SAFE_RELEASE(pIndBuffer_);
	SAFE_RELEASE(pConstBuffer_);
	SAFE_RELEASE(pTex_);
}
