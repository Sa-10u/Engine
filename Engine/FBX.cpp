#include "FBX.h"
#include "LOBJ.h"

const short TRIANGLE = 3;

Fbx::Fbx():polygon(0),vertex(0),indcnt_(0)
{
	drwtype_ = SHADER_TYPE::SHADER_POINT3D;
	lght_ = &(LightManager->Light_Path1);
}

Fbx::~Fbx()
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

	char CurDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, CurDir);

	char Dir[MAX_PATH];
	_splitpath_s(fileName.c_str(), nullptr, NULL, Dir, MAX_PATH, nullptr, NULL, nullptr, NULL );

	SetCurrentDirectory(Dir);

	InitVerticies(Fmesh);
	InitIndexes(Fmesh);
	InitMaterial(child);

	InitCB();

	Fmng->Destroy();

	SetCurrentDirectory(CurDir);
	return S_OK;
}




void Fbx::Draw(Trans* wldMat)
{
	D3D::SetShader(drwtype_);

	for (int i = 0; i < material; i++) {


			CONSTANT_BUFFER cb;
			cb.VP_matWLD = XMMatrixTranspose(wldMat->GetWorldMatrix() * CAM::GetViewMatrix() * CAM::GetProjectionMatrix());
			cb.matW = XMMatrixTranspose(wldMat->GetNormalMatrix());
			cb.matWV = XMMatrixTranspose(CAM::GetViewMatrix());

			for (int i = 0; i < LIGHT_AMMOUNT; i++) {
				//cb.matLGT[i] = (*lght_->me[i]).color;
				//cb.matLGTpos[i] = XMFLOAT4{ (*lght_->me[i]).trans.pos.x,(*lght_->me[i]).trans.pos.y,(*lght_->me[i]).trans.pos.z,0};
				//cb.Type[i] = (*lght_->me[i]).GetType();
				//cb.intensity[i] = (*lght_->me[i]).intensity;

				(this->*SetCB[static_cast<bool>(lght_->me[i])])( (lght_->me[i]), i, & cb );
			}
			cb.diffuse = list_material[i].diffuse;
			cb.isTex = list_material[i].tex != nullptr;

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

			D3D::pContext_->IASetIndexBuffer(ib[i], DXGI_FORMAT_R32_UINT, 0);


			//コンスタントバッファ
			D3D::pContext_->VSSetConstantBuffers(0, 1, &(this->cb));	//頂点シェーダー用	
			D3D::pContext_->PSSetConstantBuffers(0, 1, &(this->cb));

			if (list_material[i].tex)
			{
				ID3D11SamplerState* pSampler = list_material[i].tex->GetSampler();
				D3D::pContext_->PSSetSamplers(0, 1, &pSampler);

				ID3D11ShaderResourceView* pSRV = list_material[i].tex->GetResourceV();
				D3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
			}

			D3D::pContext_->DrawIndexed(indcnt_[i], 0, 0);
	
	}
}

void Fbx::Release()
{
}

void Fbx::SetLightGroup(LIGHTMANAGER::LightGroup* grp)
{
}

void Fbx::SetShaderType(SHADER_TYPE type_)
{
	drwtype_ = type_;
}

HRESULT Fbx::InitVerticies(fbxsdk::FbxMesh* Fmesh)
{
	VERTEX* vx = new VERTEX[vertex];

	for (unsigned long int i = 0; i < polygon; i++) {
		for (int j = 0; j < TRIANGLE; j++) {

			int index = Fmesh->GetPolygonVertex(i, j);

			FbxVector4 pos = Fmesh->GetControlPointAt(index);
			vx[index].pos = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			FbxLayerElementUV* pUV = Fmesh->GetLayer(0)->GetUVs();
			int uvIndex = Fmesh->GetTextureUVIndex(i, j, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vx[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0 - uv.mData[1]), 0.0f, 0.0f);

			FbxVector4 Normal;
			Fmesh->GetPolygonVertexNormal(i, j, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			vx[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
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
	ib = new ID3D11Buffer* [material];

	indcnt_ = new int[material];
	int* ind = new int[polygon * 3];

	for (int i = 0; i < material; i++) {

		int cnt = 0;

		for (uint32_t j = 0; j < polygon; j++) {

			FbxLayerElementMaterial* mtl = Fmesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(j);

			if (mtlId == i)
			{
				for (DWORD vertex = 0; vertex < 3; vertex++) {
					ind[cnt] = Fmesh->GetPolygonVertex(j, vertex);
					cnt++;
				}
			}
		}
		indcnt_[i] = cnt;

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

		HRESULT hr = S_OK;

		hr = D3D::pDevice_->CreateBuffer(&bd, &InitData, &ib[i]);
		

		if (FAILED(hr))
		{
			return hr;
		}

	}
	delete[] ind;

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

		//テクスチャの数
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
			HRESULT hr = list_material[i].tex->Load(name);

			assert(hr == S_OK);
		}

		//テクスチャ無し
		else
		{
			list_material[i].tex = nullptr;

			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)Fmesh->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			list_material[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
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

void Fbx::Set(LOBJ *lght ,int i , CONSTANT_BUFFER* cb)
{
	cb->matLGT[i] = (*lght_->me[i]).color;
	cb->matLGTpos[i] = XMFLOAT4{ (*lght_->me[i]).trans.pos.x,(*lght_->me[i]).trans.pos.y,(*lght_->me[i]).trans.pos.z,0 };
	cb->Type[i] = (*lght_->me[i]).GetType();
	cb->intensity[i] = (*lght_->me[i]).intensity;
}

void Fbx::Unset(LOBJ *lght ,int i , CONSTANT_BUFFER* cb)
{
	cb->matLGT[i] = XMFLOAT4(0,0,0,0);
	cb->matLGTpos[i] = XMFLOAT4(0,0,0,0);
	cb->Type[i] = static_cast<int>(LIGHT_TYPE::NONE);
	cb->intensity[i] = NULL;
}
