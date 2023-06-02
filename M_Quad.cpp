#include "M_Quad.h"
#include "CONSTANT_BUFFER.h"

//#pragma comment(lib, "d3d11.lib")

M_Quad::M_Quad():pVXBuffer_(nullptr),pIndBuffer_(nullptr),pConstBuffer_(nullptr)
{
	
}

M_Quad::~M_Quad()
{
}

HRESULT M_Quad::Initialize()
{
	HRESULT hr = E_FAIL;

	XMVECTOR vx[] =
	{
		XMVectorSet(-1.0f,1.0f,0.0f,0.0f) ,
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),
	
	};


	{
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(vx);
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = vx;
		hr = D3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVXBuffer_);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Buffer_Discription has been Mistook", "ERROR", MB_OK);
			return hr;
		}
	}

	{
		int Ind[] = { 0,1,2 , 0,2,3 };
		VXs = sizeof(Ind);

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Ind);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = Ind;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		hr = D3D::pDevice->CreateBuffer(&bd, &InitData, &pIndBuffer_);

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
		hr = D3D::pDevice->CreateBuffer(&cb, nullptr, &pConstBuffer_);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Constant_Buffer has been Mistook", "ERROR", MB_OK);

			return hr;
		}
	}

	
	return S_OK;
}

void M_Quad::Draw()
{
	//コンスタントバッファに渡す情報
	XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列

	CONSTANT_BUFFER cb;
	cb.VP_matWLD = XMMatrixTranspose(view * proj);

	D3D11_MAPPED_SUBRESOURCE pdata;
	D3D::pContext->Map(pConstBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	D3D::pContext->Unmap(pConstBuffer_, 0);	//再開

	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	D3D::pContext->IASetVertexBuffers(0, 1, &pVXBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	D3D::pContext->IASetIndexBuffer(pIndBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	D3D::pContext->VSSetConstantBuffers(0, 1, &pConstBuffer_);	//頂点シェーダー用	
	D3D::pContext->PSSetConstantBuffers(0, 1, &pConstBuffer_);

	

	D3D::pContext->DrawIndexed(VXs, 0, 0);
}

void M_Quad::Release()
{
	SAFE_RELEASE(pVXBuffer_);
	SAFE_RELEASE(pIndBuffer_);
	SAFE_RELEASE(pConstBuffer_);
}
