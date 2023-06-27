#include "FBX.h"

const short TRIANGLE = 3;

Fbx::Fbx():polygon(0),vertex(0)
{
}

HRESULT Fbx::Load(std::string fileName)
{
	FbxManager* Fmng = FbxManager::Create();

	FbxImporter* Fimp = FbxImporter::Create(Fmng, "imp");
	Fimp->Initialize(fileName.c_str(), -1, Fmng->GetIOSettings());

	FbxScene* Fscene = FbxScene::Create(Fmng, "fbxscene");


	Fimp->Import(Fscene);
	Fimp->Destroy();

	FbxNode* root = Fscene->GetRootNode();
	FbxNode* child = root->GetChild(0);

	FbxMesh* Fmesh = child->GetMesh();

	vertex = Fmesh->GetControlPointsCount();
	polygon = Fmesh->GetPolygonCount();
	material = child->GetMaterialCount();

	InitVerticies(Fmesh);
	InitIndexes(Fmesh);
	InitMaterial(child);

	InitCB();

	Fmng->Destroy();
	return S_OK;
}

void Fbx::Draw(Trans* wldMat , XMFLOAT4 WorldLight)
{
	D3D::SetShader(SHADER_TYPE::SHADER_3D);

	CONSTANT_BUFFER cb;
	cb.VP_matWLD = XMMatrixTranspose(wldMat->GetWorldMatrix() * CAM::GetViewMatrix() * CAM::GetProjectionMatrix());
	cb.matW = XMMatrixTranspose(wldMat->GetNormalMatrix());
	cb.matLGT = WorldLight;

	D3D11_MAPPED_SUBRESOURCE pdata;
	D3D::pContext_->Map(this->cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	D3D::pContext_->Unmap(this->cb, 0);	//再開

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	D3D::pContext_->IASetVertexBuffers(0, 1, &this->vb, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	D3D::pContext_->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	D3D::pContext_->VSSetConstantBuffers(0, 1, &(this->cb));	//頂点シェーダー用	
	D3D::pContext_->PSSetConstantBuffers(0, 1, &(this->cb));

	ID3D11SamplerState* pSampler = list_material->tex->GetSampler();

	D3D::pContext_->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = list_material->tex->GetResourceV();

	D3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	D3D::pContext_->DrawIndexed(vertex * 3, 0, 0);
}

void Fbx::Release()
{
	SAFE_RELEASE(vb);
	SAFE_RELEASE(ib);
	SAFE_RELEASE(pb);
	SAFE_RELEASE(cb);

	SAFE_DELETE(list_material);

	//SAFE_RELEASE(tex_);
}

HRESULT Fbx::InitVerticies(fbxsdk::FbxMesh* Fmesh)
{
	VERTEX* vx = new VERTEX[vertex];

	for (unsigned long int i = 0; i < polygon; i++) {
		for (int j = 0; j < TRIANGLE; j++) {

			int index = Fmesh->GetPolygonVertex(i, j);

			FbxVector4 pos = Fmesh->GetControlPointAt(index);
			vx[index].pos = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);
		}
	}

	//---------------

	{
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = vertex * sizeof(VERTEX);
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = vx;
		HRESULT hr = D3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &vb);

		if (hr != S_OK)
		{
			MessageBox(nullptr, "Buffer_Discription has been Mistook", "ERROR", MB_OK);
			return hr;
		}
	}

	return S_OK;
}

HRESULT Fbx::InitIndexes(fbxsdk::FbxMesh* Fmesh)
{
	int* ind = new int[polygon * 3];
	int cnt = 0;

	for (unsigned long int i = 0; i < polygon; i++) {
		for (short j = 0; j < TRIANGLE; j++) {

			ind[cnt] = Fmesh->GetPolygonVertex(i, j);
			cnt++;
		}
	}

	//-------

	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * vertex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = ind;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	HRESULT hr = D3D::pDevice_->CreateBuffer(&bd, &InitData, &ib);

	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}

HRESULT Fbx::InitMaterial(fbxsdk::FbxNode* Fmesh)
{
	list_material = new MATERIAL[material];

	for (int i = 0; i < material; i++)
	{
		FbxSurfaceMaterial* pMaterial = Fmesh->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount > 0)
		{

			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);

			//ファイルからテクスチャ作成
			list_material[i].tex = new Texture;
			list_material[i].tex->Texture::Load(textureFilePath);
		}

		//テクスチャ無し
		else
		{
			list_material[i].tex = nullptr;
		}
	}

	return S_OK;
}

void Fbx::InitCB()
{
	{
		D3D11_BUFFER_DESC cb;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;

		D3D::pDevice_->CreateBuffer(&cb, nullptr, &(this->cb));

	}
}
