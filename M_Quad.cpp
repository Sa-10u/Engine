#include "M_Quad.h"


//#pragma comment(lib, "d3d11.lib")

M_Quad::M_Quad():pVXBuffer_(nullptr),pIndBuffer_(nullptr),pConstBuffer_(nullptr),VCs(NULL),pTex_(nullptr)
{
	
}

M_Quad::~M_Quad()
{
}

HRESULT M_Quad::Initialize(VERTEX vcs[],int vcw, string pic, int index[] , int inds)
{
	HRESULT hr = E_FAIL;

	//-----
	VERTEX v[] =
	{
		{XMVectorSet(1,0,0,0) , XMVectorSet(0,0,0,0)},
		{XMVectorSet(1,1,0,0) , XMVectorSet(0.25,0,0,0)},
		{XMVectorSet(0,1,0,0) , XMVectorSet(0.25,0.5,0,0)},		//1*
		{XMVectorSet(0,0,0,0) , XMVectorSet(0,0.5,0,0)},

		{XMVectorSet(1,1,1,0) , XMVectorSet(0.5,0,0,0)},		//2*
		{XMVectorSet(0,1,1,0) , XMVectorSet(0.5,0.5,0,0)},

		{XMVectorSet(1,0,1,0) , XMVectorSet(0.75,0,0,0)},
		{XMVectorSet(0,0,1,0) , XMVectorSet(0.75,0.5,0,0)},		//3*

		{XMVectorSet(1,0,0,0) , XMVectorSet(1,0,0,0)},
		{XMVectorSet(0,0,0,0) , XMVectorSet(1,0.5,0,0)},		//4*

		{XMVectorSet(0,0,0,0) , XMVectorSet(0,1,0,0)},			//5
		{XMVectorSet(0,0,0,0) , XMVectorSet(0.25,1,0,0)},

		{XMVectorSet(0,0,1,0) , XMVectorSet(0.5,1,0,0)},		//6

	};

	int i[] =
	{
		0,1,2, 0,2,3, 1,4,5, 1,5,2, 4,6,7, 4,7,5, 6,8,9, 6,9,7, 3,2,11, 3,11,10 ,2,5,12, 2,12,11
	};
	//-----

	{
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth =vcw;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = v;
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
		bd.ByteWidth = inds;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = i;
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
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		// コンスタントバッファの作成
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

HRESULT M_Quad::Initialize()
{
	VERTEX vx[] =
	{
		XMVectorSet(-1.0f,1.0f,0.0f,0.0f) ,
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),

	};

	int Ind[] = { 0,1,2 , 0,2,3 };

	HRESULT res;

	res = this->Initialize(ARRAY_WITH_SIZE(vx), "Assets/dice.png", ARRAY_WITH_SIZE(Ind));

	return res;
}

void M_Quad::Draw(XMMATRIX* wldMat)
{
	
	CONSTANT_BUFFER cb;
	cb.VP_matWLD = XMMatrixTranspose(*wldMat * CAM::GetViewMatrix() * CAM::GetProjectionMatrix());

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

void M_Quad::Release()
{
	SAFE_RELEASE(pVXBuffer_);
	SAFE_RELEASE(pIndBuffer_);
	SAFE_RELEASE(pConstBuffer_);
	SAFE_RELEASE(pTex_);
}
