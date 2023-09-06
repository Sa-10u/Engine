#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/DInput.h"

Stage::Stage(GOBJ* parent):GOBJ(parent,"Stage")
{
}

void Stage::Initialize()
{
	string base_ = "assets/";
	string names_[static_cast<int>(BLOCKTYPE::AMMOUNT)] =
	{
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	for (int i = 0; i < sizeof(names_) / sizeof(names_[0]); i++) {

		model_[i] = Model::Load(base_ + names_[i]);
		assert(model_[i] != -1);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			
			Table[x* XSIZE + z].blk = BLOCKTYPE((x + z) % 5);
			Table[x * XSIZE + z].height = z / 4;
		}
	}
	
}

void Stage::Update()
{
	float w = static_cast<float>(D3D::Width_ / 2);
	float h = static_cast<float>(D3D::Height_ / 2);

	XMMATRIX vp =
	{
		w,	0,	0,	0,
		0, -h,	0,	0,
		0,	0,	1,	0,
		w,	h,	0,	1,
	};

	XMMATRIX inv_vp = XMMatrixInverse(nullptr, vp);
	XMMATRIX inv_proj = XMMatrixInverse(nullptr, CAM::projMat_);
	XMMATRIX inv_view = XMMatrixInverse(nullptr, CAM::viewMat_);

	XMFLOAT3 mousePosFront = {};
	{
		mousePosFront.x = Input::GetMousePosition().x;
		mousePosFront.y = Input::GetMousePosition().y;
	}

	XMVECTOR Front = XMLoadFloat3(&mousePosFront);
	Front = XMVector3Transform(Front,(inv_view * inv_proj * inv_vp));
	XMStoreFloat3(&mousePosFront, Front);


	XMFLOAT3 mousePosBack = {};
	{
		mousePosBack.z = 1.0f;

		mousePosBack.x = Input::GetMousePosition().x;
		mousePosBack.y = Input::GetMousePosition().y;
	}

	XMVECTOR Back = XMLoadFloat3(&mousePosBack);
	Back = XMVector3Transform(Back, (inv_view * inv_proj * inv_vp));
	XMStoreFloat3(&mousePosBack, Back);

	RAYCAST_DATA ray = {};
	ray.begin = mousePosFront;
	ray.end = mousePosBack;
	
	int num = 0;

	if (Model::RayCast(&num, &ray))
	{
		int i = true;
	}
}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			Trans sttrans;
			for (int i = 0; i <= Table[x * XSIZE + z].height; i++) {

				sttrans.pos = { (float)x,static_cast<float>(i) ,(float)z };

				auto number = static_cast<int>(Table[x * XSIZE + z].blk);

				Model::Draw(&number, &sttrans, SHADER_TYPE::SHADER_2D);
			}
		}
	}
	
}

void Stage::Release()
{
}

void Stage::SetBlockType(int x, int y, BLOCKTYPE type)
{
	Table[x * XSIZE + y].blk = type;
}

BLOCKTYPE Stage::GetBlockType(int x, int y)
{
	return static_cast<BLOCKTYPE>(Table[x * XSIZE + y].blk);
}

void Stage::SetHeight(int x, int y, int h)
{
	Table[x * XSIZE + y].height = h;
}

int Stage::GetHeight(int x, int y)
{
	return Table[x * XSIZE + y].height;
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG	:	SendMessage(GetDlgItem(hDlg, IDR_UP), BM_SETCHECK, BST_CHECKED, NULL);
	{
		LPCSTR names_[static_cast<int>(BLOCKTYPE::AMMOUNT)] =
		{
			"BoxDefault.fbx",
			"BoxBrick.fbx",
			"BoxGrass.fbx",
			"BoxSand.fbx",
			"BoxWater.fbx"
		};
		for (int i = 0; i < static_cast<int>(BLOCKTYPE::AMMOUNT); i++) {
			SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, NULL, (LPARAM)(names_[i]));
		}
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0,NULL);
	}
		return true;	

	 case WM_COMMAND:	select_ = static_cast<SELECT>(SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, NULL, NULL));
						mode_ = static_cast<MODE>(LOWORD(wp) - IDR_UP);
						return true;

	}

	return FALSE;
}
