#include "M_Quad.h"
#include "CONSTANT_BUFFER.h"

//#pragma comment(lib, "d3d11.lib")

M_Quad::M_Quad():pVXBuffer_(nullptr),pIndBuffer_(nullptr),pConstBuffer_(nullptr)
{
	
}

M_Quad::~M_Quad()
{
}

void M_Quad::Initialize()
{
	XMVECTOR vx[] =
	{
		XMVectorSet(-1.0f,1.0f,0.0f,0.0f) ,
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f)
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
		D3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVXBuffer_);
	}

	{
		int Ind[] = { 0,1,2 , 0,2,3 };

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
		D3D::pDevice->CreateBuffer(&bd, &InitData, &pIndBuffer_);
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
		D3D::pDevice->CreateBuffer(&cb, nullptr, &pConstBuffer_);
	}



}

void M_Quad::Draw()
{
}

void M_Quad::Release()
{
	pVXBuffer_->Release();
	pIndBuffer_->Release();
	pConstBuffer_->Release();
}
